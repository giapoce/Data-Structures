// Fig. 8.5: string1.h
// Definition of a String class

// (C) Copyright 2000 by Deitel & Associates, Inc. and Prentice Hall.*

// modified by Gianmarco Iapoce on 28 - 06 - 2003

#ifndef ISTRING1_H
#define ISTRING1_H

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cassert>

using std::ostream;
using std::istream;
using std::cout;
using std::endl;
using std::setw;

class IString {
   friend ostream &operator<<( ostream &, const IString & );
   friend istream &operator>>( istream &, IString & );

public:
   IString( const char * = "" ); // conversion/default ctor
   IString( const IString & );    // copy constructor
   ~IString();                   // destructor
   const IString &operator=( const IString & );  // assignment
   const IString &operator+=( const IString & ); // concatenation
   bool operator!() const;                  // is IString empty?
   bool operator==( const IString & ) const; // test s1 == s2
   bool operator<( const IString & ) const;  // test s1 < s2

   // test s1 != s2
   bool operator!=( const IString & right ) const
      { return !( *this == right ); }

   // test s1 > s2
   bool operator>( const IString &right ) const
      { return right < *this; }
 
   // test s1 <= s2
   bool operator<=( const IString &right ) const
      { return !( right < *this ); }

   // test s1 >= s2
   bool operator>=( const IString &right ) const
      { return !( *this < right ); }

   char &operator[]( int );             // subscript operator
   const char &operator[]( int ) const; // subscript operator
   IString operator()( int, int );       // return a substring
   int getLength() const;    // return string length

/*These changes are mine*/

   class _iterator
		{
			friend class IString;
			public:	
				_iterator() {_chars = 0; curr_index=0;}
				_iterator(char *_c, int curr_idx) {_chars = _c; curr_index=curr_idx;}
				bool operator==(const _iterator &i) {return i.curr_index==curr_index;}
				bool operator!=(const _iterator &i) {return i.curr_index!=curr_index;}
				bool operator>(const _iterator &i) {return i.curr_index<curr_index;}
				bool operator<(const _iterator &i) {return i.curr_index>curr_index;}
				bool operator>=(const _iterator &i) {return i.curr_index<=curr_index;}
				bool operator<=(const _iterator &i) {return i.curr_index>=curr_index;}
				_iterator &operator++() {++curr_index; return *this;}
				_iterator operator++(int) {_iterator temp = *this; ++(*this); return temp;}
				_iterator &operator--() {--curr_index; return *this;}
				_iterator operator--(int) {_iterator temp = *this; --(*this); return temp;}
				_iterator &operator+=(int i) {curr_index+=i; return *this;}
				_iterator &operator-=(int i) {curr_index-=i; return *this;}
				_iterator operator+(int i) {_iterator tmp = *this; return (tmp += i);}
				_iterator operator-(int i) {_iterator tmp = *this; return (tmp -= i);}
				int operator-(const _iterator &i) {return abs(i.curr_index - curr_index);}
				int operator+(const _iterator &i) {return (i.curr_index + curr_index);}
				char operator[](int _N) {return (*(*this + _N));} 
				char operator*() const {return _chars[curr_index];}
				char operator*() {return _chars[curr_index];}
				int index() {return curr_index;}
			private:
				int curr_index;
				char *_chars;
		};
		_iterator begin() const;
		_iterator end() const;
		_iterator rbegin() const;
		_iterator rend() const;
	
		/*End of changes by me*/

private:
   int length;                   // string length 
   char *sPtr;                   // pointer to start of string
   void setString( const char * );  // utility function
};


// Fig. 8.5: string1.cpp
// Member function definitions for class String

// Conversion constructor: Convert char * to String
IString::IString( const char *s ) : length( strlen( s ) )
{
   setString( s );         // call utility function
   cout << "Conversion constructor" << endl;
}

// Copy constructor
IString::IString( const IString &copy ) : length( copy.length )
{
   setString( copy.sPtr ); // call utility function
}

// Destructor
IString::~IString()
{
   delete [] sPtr;         // reclaim string
}

// Overloaded = operator; avoids self assignment
const IString &IString::operator=( const IString &right )
{

   if ( &right != this ) {         // avoid self assignment
      delete [] sPtr;              // prevents memory leak
      length = right.length;       // new String length
      setString( right.sPtr );     // call utility function
   }
   else
      cout << "Attempted assignment of a String to itself\n";

   return *this;   // enables cascaded assignments
}

// Concatenate right operand to this object and
// store in this object.
const IString &IString::operator+=( const IString &right )
{
   char *tempPtr = sPtr;        // hold to be able to delete
   length += right.length;      // new String length
   sPtr = new char[ length + 1 ]; // create space
   assert( sPtr != 0 );   // terminate if memory not allocated
   strcpy( sPtr, tempPtr );     // left part of new String
   strcat( sPtr, right.sPtr );  // right part of new String
   delete [] tempPtr;           // reclaim old space
   return *this;                // enables cascaded calls
}

// Is this String empty?
bool IString::operator!() const { return length == 0; }

// Is this String equal to right String?
bool IString::operator==( const IString &right ) const
   { return strcmp( sPtr, right.sPtr ) == 0; }

// Is this String less than right String?
bool IString::operator<( const IString &right ) const
   { return strcmp( sPtr, right.sPtr ) < 0; }

// Return a reference to a character in a String as an lvalue.
char &IString::operator[]( int subscript )
{
   // First test for subscript out of range
   assert( subscript >= 0 && subscript < length );

   return sPtr[ subscript ];  // creates lvalue
}

// Return a reference to a character in a String as an rvalue.
const char &IString::operator[]( int subscript ) const
{
   // First test for subscript out of range
   assert( subscript >= 0 && subscript < length );

   return sPtr[ subscript ];  // creates rvalue
}

// Return a substring beginning at index and
// of length subLength
IString IString::operator()( int index, int subLength )
{
   // ensure index is in range and substring length >= 0
   assert( index >= 0 && index < length && subLength >= 0 );

   // determine length of substring
   int len;

   if ( ( subLength == 0 ) || ( index + subLength > length ) )
      len = length - index;
   else
      len = subLength;

   // allocate temporary array for substring and 
   // terminating null character
   char *tempPtr = new char[ len + 1 ];
   assert( tempPtr != 0 ); // ensure space allocated

   // copy substring into char array and terminate string
   strncpy( tempPtr, &sPtr[ index ], len );
   tempPtr[ len ] = '\0';

   // Create temporary String object containing the substring
   IString tempString( tempPtr );
   delete [] tempPtr;  // delete the temporary array

   return tempString;  // return copy of the temporary String
}

// Return string length
int IString::getLength() const { return length; }

// Utility function to be called by constructors and 
// assignment operator.
void IString::setString( const char *string2 )
{
   sPtr = new char[ length + 1 ]; // allocate storage
   assert( sPtr != 0 );  // terminate if memory not allocated
   strcpy( sPtr, string2 );       // copy literal to object
}

// Overloaded output operator
ostream &operator<<( ostream &output, const IString &s )
{
   int LEN = s.length;
   for (int i=0; i<LEN; ++i)
			output << s.sPtr[i] << '/';
   return output;   // enables cascading
}

// Overloaded input operator
istream &operator>>( istream &input, IString &s )
{
   char temp[ 100 ];   // buffer to store input

   input >> setw( 100 ) >> temp;
   s = temp;        // use String class assignment operator
   return input;    // enables cascading
}


// Changes made by me.

IString::_iterator IString::begin() const
{
	return IString::_iterator(sPtr,0);
}

IString::_iterator IString::end() const
{
	return IString::_iterator(sPtr,length);
}

IString::_iterator IString::rbegin() const
{
	return IString::_iterator(sPtr,length-1);
}

IString::_iterator IString::rend() const
{
	return IString::_iterator(sPtr,-1);
}

// End of changes.

#endif



