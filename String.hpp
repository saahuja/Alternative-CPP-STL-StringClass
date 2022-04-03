

#include <iostream>
#include <cstring>
#include "BufferManager.hpp"

#ifndef String_h
#define String_h

//Created by Sahil Ahuja on 1/15/21

namespace ASTL {

    class String {
    public:

        String(const String& aString = String("", 0), size_t aPresize = 0);
        String(const char* aBuffer = "", size_t aPresize = 0);
        ~String();
        String& operator=(const String& aCopy);
        String& operator=(const char* aBuffer);

        //accessors...
        size_t size() const;

        //mutation methods...

        char& operator[](int pos);

        String  operator+(const String& aString);  //append (construct) methods
        String  operator+(const char* aBuffer);

        String& operator+=(const String& aString);  //append (to self) methods
        String& operator+=(const char* aBuffer);

        String& insert(size_t anIndex = 0, const String& aString = String(""), size_t aMaxCopyLen = 0);
        String& insert(size_t anIndex = 0, const char* aString = "", size_t aMaxCopyLen = 0);

        String& replace(size_t anIndex = 0, size_t aMaxCopyLen = 0, const String& aSubString = String(""));
        String& replace(size_t anIndex = 0, size_t aMaxCopyLen = 0, const char* aSubString = "");


        String& erase(size_t anIndex, size_t aCount); //from given position, remove N chars...("cut")


          //Comparision methods...

        int compare(const String& aString) const; //[-1 if <, 0 if ==, 1 if >]

        bool operator==(const String& aString) const;
        bool operator==(const char* aBuffer) const;

        bool operator<(const String& aString) const;
        bool operator<(const char* aBuffer) const;

        //Search...
        int find(const String& aSubString, size_t anOffset = 0) const;


        //stream...
        friend std::ostream& operator << (std::ostream& out, const String& aStr) {
            out << aStr.mainBuffer.getBuffer();
            return out;
        }
        friend std::istream& operator >> (std::istream& in, String& aString) { //change me
            in >> aString.mainBuffer.getBuffer();
            return in;
        }



    protected:
        ASTL::BufferManager mainBuffer; //serves as delegate compositionally
    };

}
#endif /* String_hpp */

