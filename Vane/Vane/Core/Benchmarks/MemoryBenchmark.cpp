#include "MemoryBenchmark.hpp"

#include <Vane/Core/Logger.hpp>
#include <Vane/Core/Asserts.hpp>
#include <cstdlib>

using namespace Vane;

void MemoryBenchmark::SingleAllocation(Allocator* allocator, const u_size size, const u8 alignment) {
  VINFO("MEMORY BENCHMARK: Allocation")  
  VINFO("\tSize:\t{}", size)
  VINFO("\tAlignment:\t{}", alignment)
  
  StartRound();

  allocator->Init();
  auto operations = 0u;

  while (operations < m_nOperations) {
    allocator->Allocate(size, alignment);
    operations++;
  }

  FinishRound();

  MemoryBenchmarkResults results = buildResults(m_nOperations, std::move(m_timeElapsed), allocator->m_peak);

  PrintResults(results);
}

void MemoryBenchmark::SingleFree(Allocator* allocator, const u_size size, const u8 alignment) {
  VINFO("MEMORY BENCHMARK: Free/Allocation")  
  VINFO("\tSize:\t{}", size)
  VINFO("\tAlignment:\t{}", alignment)
  
  void* addresses[OPERATIONS];

  StartRound();

  allocator->Init();
  auto operations = 0u;

  while (operations < m_nOperations) {
    addresses[operations] = allocator->Allocate(size, alignment);
    operations++;
  }

  while(operations) {
    allocator->Free(addresses[--operations]);
  }

  FinishRound();

  MemoryBenchmarkResults results = buildResults(m_nOperations, std::move(m_timeElapsed), allocator->m_peak);

  PrintResults(results);
}

void MemoryBenchmark::MultipleAllocation(Allocator* allocator, const std::vector<u_size>& allocationSizes, const std::vector<u8>& alignments) {
  VASSERT_MSG(allocationSizes.size() == alignments.size(), "Allocation sizes and alignments must have the same size")

  for (auto i = 0u; i < allocationSizes.size(); i++) {
    SingleAllocation(allocator, allocationSizes[i], alignments[i]);
  }
}

void MemoryBenchmark::MultipleFree(Allocator* allocator, const std::vector<u_size>& allocationSizes, const std::vector<u8>& alignments) {
  VASSERT_MSG(allocationSizes.size() == alignments.size(), "Allocation sizes and alignments must have the same size")

  for (auto i = 0u; i < allocationSizes.size(); i++) {
    SingleFree(allocator, allocationSizes[i], alignments[i]);
  }
}

void MemoryBenchmark::RandomAllocation(Allocator* allocator, const std::vector<u_size>& allocationSizes, const std::vector<u8>& alignments) {
  srand(1);

  VINFO("MEMORY BENCHMARK: Random Allocation")

  StartRound();

  u_size allocation_size;
  u_size alignment;

  allocator->Init();

  auto operations = 0u;

  while (operations < m_nOperations) {
    this -> RandomAllocationAttr(allocationSizes, alignments, allocation_size, alignment);
    allocator->Allocate(allocation_size, alignment);
    ++operations;
  }

  FinishRound();

  MemoryBenchmarkResults results = buildResults(m_nOperations, std::move(m_timeElapsed), allocator->m_peak);

  PrintResults(results);
}

void MemoryBenchmark::RandomFree(Allocator* allocator, const std::vector<u_size>& allocationSizes, const std::vector<u8>& alignments) {
  srand(1);

  VINFO("MEMORY BENCHMARK: Random Free")


  StartRound();

  void* addresses[OPERATIONS];

  u_size allocation_size;
  u_size alignment;

  allocator->Init();

  auto operations = 0u;

  while (operations < m_nOperations) {
    this -> RandomAllocationAttr(allocationSizes, alignments, allocation_size, alignment);
    addresses[operations] = allocator->Allocate(allocation_size, alignment);
    ++operations;
  }

  while(operations) {
    allocator->Free(addresses[--operations]);
  }

  FinishRound();

  MemoryBenchmarkResults results = buildResults(m_nOperations, std::move(m_timeElapsed), allocator->m_peak);

  PrintResults(results);
}

void MemoryBenchmark::PrintResults(const MemoryBenchmarkResults& results) const {
  VINFO("MEMORY BENCHMARK: Results")
  VINFO("\t\tOperations:\t{}", results.Operations)
  VINFO("\t\tMilliseconds:\t{}", results.Milliseconds.count())
  VINFO("\t\tOperations per second:\t{}", results.OperationsPerSec)
  VINFO("\t\tTime per operation:\t{}", results.TimePerOperation)
  VINFO("\t\tMemory peak:\t{}\n", results.MemoryPeak)
}

const MemoryBenchmarkResults MemoryBenchmark::buildResults(u_size nOperations, std::chrono::milliseconds&& elapsedTime, const u_size memoryPeak) const {
  MemoryBenchmarkResults results;
  results.Operations = nOperations;
  results.Milliseconds = std::move(elapsedTime);
  results.OperationsPerSec = nOperations / static_cast<f64>(results.Milliseconds.count());
  results.TimePerOperation = static_cast<f64>(results.Milliseconds.count()) / static_cast<double>(results.Operations);
  results.MemoryPeak = memoryPeak;

  return results;
}

void MemoryBenchmark::RandomAllocationAttr(const std::vector<u_size>& allocationSizes, const std::vector<u8>& alignments, u_size& size, u_size& alignment) {
  const int r = rand() % allocationSizes.size();
  size = allocationSizes[r];
  alignment = alignments[r];
}