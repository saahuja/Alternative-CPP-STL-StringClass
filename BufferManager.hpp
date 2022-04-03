

#include <cstring>
#include <iostream>
#ifndef BufferManager_hpp
#define BufferManager_hpp

//Created by Sahil Ahuja on 1/15/21

namespace ASTL {

	//BufferManager object serves the String class as a delegate
	//allocate to heap
	class BufferManager {
	public:

		BufferManager(size_t aSize = 0);
		BufferManager(const BufferManager& aManager);
		~BufferManager();
		BufferManager operator=(const BufferManager& aManager);

		//size me method
		//extend method (increase size of buffer by a fixed amount, if nothing is specified then assuming 1)
		//decrease method (decrease size of buffer by a fixed amount, if nothing is specified then assuming 1)
		//assign method (assigns a const char * to mainBuffer, and automatically adjusts to match


		size_t bufferSize() const;
		size_t stringSize() const;

		void extend(const size_t& anAmount);
		void decrease(const size_t& anAmount);
		void assign(const char* aString); //check how to pass a const reference to const char *
		//void clear() { free(mainBuffer); }  //clears buffer

		char* getBuffer() const {
			return mainBuffer;
		}
		void updateBuffer(const size_t& anIndex = 0, const char aChar = '\0'); //replace a char in buffer

		void insertAt(const char* aString, const size_t& anIndex); //insert String at position

		friend std::ostream& operator << (std::ostream& out, const BufferManager& aStr) {
			out << aStr.mainBuffer;
			return out;
		}




	protected:
		char* mainBuffer; //main protected member
		size_t bufferLength;


	};
}

#endif