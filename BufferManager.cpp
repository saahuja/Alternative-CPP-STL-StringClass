

#include "BufferManager.hpp"
#include <vector>

//Created by Sahil Ahuja on 1/15/21

namespace ASTL {

	BufferManager::BufferManager(size_t aSize) {
		if (0 == aSize) {
			mainBuffer = nullptr;
			bufferLength = aSize;
		}
		else {
			(*this).extend(aSize);
			bufferLength += bufferLength;
		}
	}

	BufferManager::BufferManager(const BufferManager & aManager) {
		mainBuffer = aManager.mainBuffer;
		bufferLength = aManager.bufferLength;
	}

	BufferManager::~BufferManager() {
		delete [] mainBuffer;
	}

	BufferManager BufferManager::operator=(const BufferManager & aManager) {
		mainBuffer = aManager.mainBuffer;
		bufferLength = aManager.bufferLength;
		return (*this);
	}

	size_t BufferManager::bufferSize() const { //size of buffer (includes any empty spots)
		return bufferLength;
	}


	size_t BufferManager::stringSize() const { //size of buffer (includes any empty spots)
		if (mainBuffer == nullptr || strlen(mainBuffer) == 0) { return 0; }

		return strlen(mainBuffer);
	}

	//change me
	void BufferManager::extend(const size_t & anAmount) {
		/*locally store the current size of the buffer
		 locally store the current buffer
		 delete what mainBuffer is currently pointing to
		 recreate new buffer and reassign mainBuffer pointer
		*/
		size_t originalSize = bufferLength;
		size_t sizeDesired = originalSize + anAmount;
		std::vector<char> localVecCopy;
		const char* localCopy;

		for (size_t i = 0; i < originalSize; i++) {
			localVecCopy.push_back(mainBuffer[i]);
		}
		localVecCopy.push_back('\0');
		localCopy = localVecCopy.data();

		delete[] mainBuffer;

		mainBuffer = new char[sizeDesired+1];
		bufferLength = sizeDesired+1;
		strcpy(mainBuffer, localCopy);
	}

	//change me
	void BufferManager::decrease(const size_t & anAmount) {
		//repeats opposite of extend
		size_t originalSize = bufferLength;
		size_t sizeDesired = originalSize - anAmount;
		std::vector<char> localVecCopy;
		const char* localCopy;

		for (size_t i = 0; i < originalSize; i++) {
			localVecCopy.push_back(mainBuffer[i]);
		}
		localVecCopy.push_back('\0');
		localCopy = localVecCopy.data();

		delete[] mainBuffer;

		mainBuffer = new char[sizeDesired+1];
		bufferLength = sizeDesired+1;
		strcpy(mainBuffer, localCopy);
	}


	void BufferManager::assign(const char* aString) {
		if (0 == bufferLength) {
			mainBuffer = new char[strlen(aString)+1];
			bufferLength = strlen(aString)+1;
			strcpy(mainBuffer, aString);
		}
		else if (bufferLength > strlen(aString)) {
			strcpy(mainBuffer, aString);
		}
		else { //aString length less than mainBuffer's space
			delete[] mainBuffer;
			mainBuffer = new char[strlen(aString)+1];
			bufferLength = strlen(aString)+1;
			strcpy(mainBuffer, aString);
		}
	}

	/*change me*/
	void BufferManager::insertAt(const char* aString, const size_t & anIndex) {
		/*
			Case 1. inserting at the beginning (2 parts)
			Case 2. inserting in the middle (3 parts)
			Case 3. inserting at the end (2 parts)

		*/

		size_t lengthNeeded = strlen(aString) + strlen(mainBuffer) + 1;
		int check = bufferLength - (lengthNeeded);
	
		//set internal member	
	   if (check > 0) { //if previously more space was allocated, this is kept
		   lengthNeeded += check;
	   }

	   bufferLength = lengthNeeded;


	   if (0 == anIndex) //if at beginning
	   {
		   const char* localPart1 = aString;
		   std::vector<char> localPartVec;
		   const char* localPart2;
		
		   for (size_t i = 0; i < strlen(mainBuffer); i++) {
			   localPartVec.push_back(mainBuffer[i]);
		   }
		    
		   delete [] mainBuffer;

		   mainBuffer = new char[bufferLength];
		   strcpy(mainBuffer, localPart1);
		   
		   localPartVec.push_back('\0');
		   localPart2 = localPartVec.data();
		   
		   strcat(mainBuffer, localPart2);
	   }

	   else if (anIndex >= strlen(mainBuffer)) { //at end
		   const char* localPart1;
		   std::vector<char> localPartVec;
		   const char* localPart2 = aString;

		   for (size_t i = 0; i < strlen(mainBuffer); i++) {
			   localPartVec.push_back(mainBuffer[i]);
		   }
		      
		   delete[] mainBuffer;

		   mainBuffer = new char[bufferLength];

		   localPartVec.push_back('\0');
		   localPart1 = localPartVec.data();
		   strcpy(mainBuffer, localPart1);
		   strcat(mainBuffer, localPart2);
	   }
	   //[* * * * * * * * *]
	  else { //in the middle

		   const char* localPart1;
		   std::vector<char> localPartVec1;
		   const char* localPart2;
		   const char* localPart3;
		   std::vector<char> localPartVec2;

		  for (size_t i = 0; i < anIndex; i++) {
			  localPartVec1.push_back(mainBuffer[i]);
		  }
		  localPartVec1.push_back('\0');
		  localPart1 = localPartVec1.data();

		  localPart2 = aString;

		  size_t condition = strlen(mainBuffer) - anIndex; //remaining elements of mainBuffer
		  size_t start = (strlen(mainBuffer) - condition);

		  for (start = start; start < strlen(mainBuffer); start++) {
			  localPartVec2.push_back(mainBuffer[start]);
		  }
		  localPartVec2.push_back('\0');
		  localPart3 = localPartVec2.data();

		  delete[] mainBuffer;

		  mainBuffer = new char[bufferLength];

		  strcpy(mainBuffer, localPart1);
		  strcat(mainBuffer, localPart2);
		  strcat(mainBuffer, localPart3);
	  }

	}

	void BufferManager::updateBuffer(const size_t & anIndex, const char aChar) {
		mainBuffer[anIndex] = aChar;
	}


}


