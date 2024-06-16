#include <iostream>

#include <Vane/Core/Application.hpp>
#include <Vane/Core/Benchmarks/MemoryBenchmark.hpp>
#include <Vane/Core/Mem/CAllocator.hpp>
#include <Vane/Core/Mem/StackAllocator.hpp>
#include <Vane/Core/Mem/LinearAllocator.hpp>
#include <Vane/Core/Logger.hpp>
#include <Vane/EntryPoint.hpp>
#include <Vane/Platform/Platform.hpp>

class Game : public Vane::Application {
public:
    Game(const Vane::ApplicationConfig &config) : Vane::Application(config) {}

    void onInit() override { 
        const u_size A = static_cast<u_size>(1e9);
        const u_size B = static_cast<u_size>(1e8);

    const std::vector<u_size> ALLOCATION_SIZES {32, 64, 256, 512, 1024, 2048, 4096};
    const std::vector<u8> ALIGNMENTS {8, 8, 8, 8, 8, 8, 8};

    using namespace Vane;

    Allocator * cAllocator = new CAllocator();
    Allocator * linearAllocator = new LinearAllocator(A);
    Allocator * stackAllocator = new StackAllocator(A);
    //Allocator * poolAllocator = new PoolAllocator(16777216, 4096);
    //Allocator * freeListAllocator = new FreeListAllocator(B, FreeListAllocator::PlacementPolicy::FIND_FIRST);

    MemoryBenchmark benchmark(OPERATIONS);

    VINFO("C")
    benchmark.MultipleAllocation(cAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    benchmark.MultipleFree(cAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    benchmark.RandomAllocation(cAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    benchmark.RandomFree(cAllocator, ALLOCATION_SIZES, ALIGNMENTS); 

    VINFO("Linear")
    benchmark.MultipleAllocation(linearAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    benchmark.RandomAllocation(linearAllocator, ALLOCATION_SIZES, ALIGNMENTS);

    VINFO("Stack")
    benchmark.MultipleAllocation(stackAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    benchmark.MultipleFree(stackAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    benchmark.RandomAllocation(stackAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    benchmark.RandomFree(stackAllocator, ALLOCATION_SIZES, ALIGNMENTS);

    /*
    std::cout << "POOL" << std::endl;
    benchmark.SingleAllocation(poolAllocator, 4096, 8);
    benchmark.SingleFree(poolAllocator, 4096, 8);

    std::cout << "FREE LIST" << std::endl;
    benchmark.MultipleAllocation(freeListAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    benchmark.MultipleFree(freeListAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    benchmark.RandomAllocation(freeListAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    benchmark.RandomFree(freeListAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    */
    
    delete cAllocator;
    delete linearAllocator;
    delete stackAllocator;
    //delete poolAllocator;

    }

    void onShutdown() override { VDEBUG("onShutdown called..."); }

    void onUpdate(f32 ms) override {
        // VDEBUG("onUpdate called...");
    }
};

Vane::Application *Vane::CreateApplication(int argc, char **argv) {
    const ApplicationConfig config = {
            .startPosX = 110,
            .startPosY = 100,
            .windowWidth = 500,
            .windowHeight = 500,
            .name = "Vane Sandbox",
    };
    
    
    const auto app = new Game(config);
    
    return app;
}
