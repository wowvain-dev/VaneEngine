#pragma once

#include <time.h>
#include <chrono>
#include <ratio>
#include <vector>

#include <Vane/Core/Defines.hpp>
#include <Vane/Core/Mem/Allocator.hpp>

namespace Vane {
#define OPERATIONS (10)

struct MemoryBenchmarkResults {
  u_size Operations;
  std::chrono::milliseconds Milliseconds;
  f64 OperationsPerSec;
  f64 TimePerOperation;
  u_size MemoryPeak;
};

class MemoryBenchmark {
private:
  u_size m_nOperations;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_finish;
  std::chrono::milliseconds m_timeElapsed;
public:
  MemoryBenchmark() = delete;
  MemoryBenchmark(const unsigned int nOperations): m_nOperations {nOperations} {}

  void SingleAllocation(Allocator* allocator, const u_size size, const u8 alignment);
  void SingleFree(Allocator* allocator, const u_size size, const u8 alignment);

  void MultipleAllocation(Allocator* allocator, const std::vector<u_size>& allocationSizes, const std::vector<u8>& alignments);
  void MultipleFree(Allocator* allocator, const std::vector<u_size>& allocationSizes, const std::vector<u8>& alignments);

  void RandomAllocation(Allocator* allocator, const std::vector<u_size>& allocationSizes, const std::vector<u8>& alignments);
  void RandomFree(Allocator* allocator, const std::vector<u_size>& allocationSizes, const std::vector<u8>& alignments);

private:
  void PrintResults(const MemoryBenchmarkResults& results) const;
  void RandomAllocationAttr(const std::vector<u_size>& allocationSizes, const std::vector<u8>& alignments, u_size& size, u_size& alignment);
  const MemoryBenchmarkResults buildResults(u_size nOperations, std::chrono::milliseconds&& elapsedTime, const u_size memoryPeak) const;

  void SetStartTime() noexcept { m_start = std::chrono::high_resolution_clock::now(); } 
  void SetFinishTime() noexcept { m_finish = std::chrono::high_resolution_clock::now(); }
  void SetElapsedTime() noexcept { m_timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(m_finish - m_start); }
  void StartRound() noexcept { SetStartTime(); } 
  void FinishRound() noexcept {
    SetFinishTime();
    SetElapsedTime(); 
  }

};

}
