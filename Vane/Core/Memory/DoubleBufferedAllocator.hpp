#pragma once 

#include "StackAllocator.hpp"
#include "../Defines.hpp"
#include "../Asserts.hpp"
#include "../Logger.hpp"

namespace Vane::Memory {

	/// @brief A double buffered allocator is a wrapper on top of the stack
	/// allocator. It holds two stack allocators (A, B) and marks one of 
	/// them as an active stack allocator each frame. At the end of each frame
	/// it swaps A and B and clears the newly activated one. For example 
	/// if A is the active allocator of frame n, all memory allocation
	/// requests will be handled by A during frame n. At the end of frame
	/// n, B becomes the active allocator and is cleared. So during frame n+1
	/// memory allocation will be done by B, and those pointers to memory in A
	/// are still valid. At the end of n + 1, A is again activated and cleared.	
	class DoubleBufferedAllocator {
	private:
		DoubleBufferedAllocator() = delete;
		explicit DoubleBufferedAllocator(u_size size);
		~DoubleBufferedAllocator() = default;

		/// @brief Grab properly aligned raw memory from the double buffered allocator.
		/// The memory will be automatically cleared at the end of next frame
		///
		/// @param size Size in byte
		/// @param alignment Alignment requirement for this memory. Must be power of 2
		/// and less than 256
		///
		/// @return Raw memory pointer, use with caution!
		void* alloc(u_size size, u8 alignment = MemUtil::ALIGNMENT);

		/// @brief Swap the active stack allocator
		void swapBuffer();

		/// @brief Clears the currently active stack allocator
		void clearCurrentBuffer();

		/// @brief Creates a new object on the active stack allocator, which will become
		/// invalid at the end of next frames. You need to manually call destructor on 
		/// the object if needed.
		///
		/// @tparam T type of object
		/// @tparam args Arguments for the constructor
		///
		/// @return Pointer to new object
		template <typename T, typename... args>
		T* New(args...);

		template<typename T>
		T* NewArr(u_size length, u8 alignment);

		StackAllocator stacks[2];
		u8 curStackIndex;

		friend class MemoryManager;
	};

	template <typename T, typename ...args>
	T* DoubleBufferedAllocator::New(args... argList) {
		return stacks[curStackIndex].New<T>(argList...);
	}

	template <typename T>
	T* DoubleBufferedAllocator::NewArr(const u_size length, const u8 alignment) {
		return stacks[curStackIndex].NewArr<T>(length, alignment);
	}

};