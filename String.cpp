
#include "String.hpp"
#include <vector> //used for erase methods

//Created by Sahil Ahuja on 1/15/21

namespace ASTL {


	String::String(const String& aString, size_t aPresize) { //add 1 for null terminator (logic below auto-corrects)
		
		//mainBuffer.clear(); //overwriting anything previously
		mainBuffer.extend(aPresize);

		if (0 == aString.size()) {//aPresize doesn't matter
		}
		else if (aString.size() + 1 <= aPresize) { //if non correct aPresize argument is given, assume 0 
			mainBuffer.assign(aString.mainBuffer.getBuffer());
		}
		else if (aString.size() + 1 > aPresize) {
			size_t discrepancy = (aString.size() + 1) - aPresize;
			mainBuffer.extend(discrepancy);
			mainBuffer.assign(aString.mainBuffer.getBuffer());
		}


		//Case 1, no aPresize or incorrect aPresize argument is given -> set mainBuffer to aString
		//Case 2, larger aPresize argument given than aString length
		//Case 3, 0 aString length and 0 aString 
	}

	String::String(const char* aBuffer, size_t aPresize) { //same as above

		//mainBuffer.clear(); //overwriting anything previously
		mainBuffer.extend(aPresize);

		if (0 == strlen(aBuffer)) {//aPresize doesn't matter}
		}
		else if (strlen(aBuffer) + 1 <= aPresize) { //if non correct aPresize argument is given, assume 0 
			mainBuffer.assign(aBuffer);
		}
		else if (strlen(aBuffer) + 1 > aPresize) {
			size_t discrepancy = (strlen(aBuffer) + 1) - aPresize;
			mainBuffer.extend(discrepancy);
			mainBuffer.assign(aBuffer);
		}
	}


	String::~String() {}

	String& String::operator=(const String& aCopy) {
		mainBuffer = aCopy.mainBuffer;
		return (*this);
	}
	String& String::operator=(const char* aBuffer) {
		mainBuffer.assign(aBuffer);
		return (*this);
	}

	size_t String::size() const {
		return mainBuffer.stringSize();
	}
	
	char& String::operator[](int pos) {
		if (static_cast<size_t>(pos) >= (*this).size() || pos < 0) {
			throw std::out_of_range("Invalid index provided");
		}
		return (*this).mainBuffer.getBuffer()[pos];
	}
	
	
	String String::operator+(const String& aString) { //append (Construct) methods
		size_t originalSize = (*this).size();
		size_t spaceNeeded = aString.size();
		String toReturn((*this), (originalSize + spaceNeeded));
		toReturn.insert(originalSize, aString.mainBuffer.getBuffer(), 0);
		return toReturn;		
	}

	String String::operator+(const char* aBuffer) {
		return (*this) + (String(aBuffer));
	}
	

	String& String::operator+=(const String& aString) {  //append (to self) methods
		size_t originalSize = (*this).size();
		size_t spaceNeeded = aString.size();
		mainBuffer.extend(spaceNeeded);
		(*this).insert(originalSize, aString.mainBuffer.getBuffer(), 0);
		return (*this);
	}

	String& String::operator+=(const char* aBuffer) {
		return (*this) += (String(aBuffer));
	}

	String& String::replace(size_t anIndex, size_t aMaxCopyLen, const String& aSubString) {
		/*
			Case 1-Buffer is big enough
			Case 2-Buffer needs extension		
		*/
		if (anIndex > mainBuffer.stringSize()) {
			throw std::out_of_range("Invalid Index provided");
		}
		
		String localString(aSubString, 0);
		
		//aMaxCopyLen here is the max number of characters that can be replaced, and doesn't count spaces in the substring

		if (aMaxCopyLen == 0) {
			return insert(anIndex, aSubString, 0); //insert entire string
		}
		size_t counter = 0;
		
		int check = (mainBuffer.bufferSize()) - (anIndex + localString.size() + 1); //add one for null
		if (check < 0) {
			mainBuffer.extend(std::abs(check)); //since here it'd be negative and it needs this much more
		}
		for (size_t i = 0; i < aSubString.size(); i++) {
			mainBuffer.updateBuffer(anIndex, (localString.mainBuffer.getBuffer())[i]);
			anIndex++;
			counter++;
			if (counter >= aMaxCopyLen) { //insert rest of the string	
				size_t j = i;
				const char* hold = &(localString.mainBuffer.getBuffer())[j + 1];
				//std::cout << "Now: " << (*this).mainBuffer.getBuffer() << "\n";
				//std::cout << "Insert: " << hold << "\n";
				(*this).insert(anIndex, hold, 0);
				break;
			}
		} //mainBuffer.updateBuffer(anIndex, '\0'); //add null character
	
		(*this) += "\0"; //add null in case
		return (*this);
	}
	
	
	String& String::replace(size_t anIndex, size_t aMaxCopyLen, const char* aSubString) {
		String localCopy(aSubString);
		return (replace(anIndex, aMaxCopyLen, localCopy));
	}


	
	String& String::insert(size_t anIndex, const String& aString, size_t aMaxCopyLen) {
		/*
			Case 1-Buffer is big enough
			Case 2-Buffer needs extension
		*/

		if (anIndex > mainBuffer.stringSize()) {
			throw std::out_of_range("Invalid Index provided");
		}


		String localString(aString);
			
		
		if (aMaxCopyLen != 0) { //decrease string as needed
			if (aMaxCopyLen > aString.size()) { //take the entire string
				aMaxCopyLen = aMaxCopyLen;
			}
			else if (aMaxCopyLen < aString.size()) { //decrease the string
				localString.mainBuffer.decrease(aString.size() - aMaxCopyLen);
			}
		}
		
		
		mainBuffer.insertAt(localString.mainBuffer.getBuffer(), anIndex);
		return (*this);
	}
	
	String& String::insert(size_t anIndex, const char* aString, size_t aMaxCopyLen) {
		String localString(aString);
		return insert(anIndex, localString, aMaxCopyLen);
	}


	String& String::erase(size_t anIndex, size_t aCount) {
		if (anIndex > mainBuffer.stringSize()) {
			throw std::out_of_range("Invalid Index provided");
		}
		int check = (mainBuffer.stringSize()) - (anIndex + aCount);
		if (check < 0) { //if aCount provided is greater than the number of characters, automate this to maximum valid aCount
			aCount = mainBuffer.stringSize() - (anIndex);
		}
		
		std::vector<char> temp;
		for (size_t i = 0; i < (*this).size(); i++) {
			if (i == anIndex) {
				i += aCount;
				temp.push_back(mainBuffer.getBuffer()[i]); //push back letter before skipping
			}
			else {
				temp.push_back(mainBuffer.getBuffer()[i]);
			}
		}
		
		temp.push_back('\0');
		mainBuffer.assign(temp.data());
		return (*this);
	}
	


	bool String::operator==(const String& aString) const {
		String string1(aString, 0);
		String string2(*this);
		if (string1.size() != string2.size()) { return false; }
		for (int i = 0; i < static_cast<int>(string1.size()); i++) {
			if (string1[i] != string2[i]) {
				return false;
			}
		}
		return true;
	}

	bool String::operator==(const char* aBuffer) const {
		return (*this) == (String(aBuffer));
	}

	int String::compare(const String& aString) const {
		if ((*this) < aString) { return -1; }
		else if ((*this) == aString) { return 0; }
		else { return 1; }
	}
	
	bool String::operator<(const String& aString) const {
		const char* localString1 = (*this).mainBuffer.getBuffer();
		const char* localString2 = aString.mainBuffer.getBuffer();
		if (strcmp(localString1, localString2) < 0) {
			return true; //(*this) < aString is true
		}
		return false;
	}

	bool String::operator<(const char* aBuffer) const {
		return (*this) < (String(aBuffer));
	}

	int String::find(const String& aSubString, size_t anOffset) const {
		int toReturn(-1);
		size_t numIterations = (*this).size() - anOffset;
		String string1(aSubString, 0);
		int string1Index(0);

		if (anOffset > mainBuffer.stringSize()) {
			throw std::out_of_range("Invalid Index provided");
		}

		for (size_t i = 0; i < numIterations; i++) {
			if (string1[string1Index] == mainBuffer.getBuffer()[anOffset + i]) {
				(toReturn == -1) ? (toReturn = (i+anOffset)) : (toReturn = toReturn); //assume next few characters will be valid
				string1Index++;
				//std::cout << mainBuffer.getBuffer()[anOffset + i] << "\n";
			}
			else {
				toReturn = -1;
				string1Index = 0;
			}
			//std::cout << "Index: " << i << "\n";
			//std::cout << "string1Index " << string1Index << "\n";
			//std::cout << "aSubstring.size() " << aSubString.size() << "\n";
			if (static_cast<size_t>(string1Index) == aSubString.size()) { //if all matches were met
				break;
			}
		}

		if (static_cast<size_t>(string1Index) != aSubString.size()) { return -1; } //double check condition in case it was not met above

		return toReturn;
	}

	//change instream method


}

















