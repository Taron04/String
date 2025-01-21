#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>

class my_string{
  
   private: 
      char* m_str;
      size_t m_capacity;
      size_t m_size;
      
   public:
      my_string();                  // default constructor
      my_string(const my_string&);  // copy constructor
      my_string(const char*);       // parametic constructor
      my_string(my_string&&);       // move constructor
      ~my_string();                 // Destructor
                                 
      my_string& operator=(const my_string&); // copy assignment
      my_string& operator=(const char*);      // assignment operator
      my_string& operator=(my_string&&);      // move assignment 
   

      my_string operator+(const my_string&); // operator+
      my_string operator+(const char*);      // operator+
 
      my_string& operator+=(const my_string&); // operator+=
      my_string& operator+=(const char*);      // operator+=

      char& operator[](size_t); // subscript operator

      size_t size() const;           // returns the number of characters
      bool empty() const;            // checks whether the string is empty
      void reserve(size_t);    // reserves storage
      size_t capacity() const;       // returns the number of characters that can be held in currently allocated storage
      void shrink_to_fit();    // reduces memory usage by freeing unused memory

      char* begin(); // returns an pointer to the begining 
      const char* begin() const; //	returns an poiter to the beginning read-only
      char* end();   // returns an pointer to the end

      void clear() noexcept;  // clears the contents
      my_string& insert( size_t index, size_t count, char ch );       // inserts characters
      my_string& insert( size_t index, const char* s );               // inserts characters
      my_string& insert( size_t index, const char* s, size_t count ); // inserts characters
      my_string& insert( size_t index, const my_string& str );        // inserts characters

      void push_back( char ch ); // appends a character to the end
      void pop_back();           // removes the last character

                                            
      void resize( size_t count, char ch ); // changes the number of characters stored
 
      void swap( my_string& other ) noexcept; // swaps the contents

      constexpr size_t find( const my_string& str, size_t pos = 0 ) const// finds the first occurrence of the given substring  
      {
         if(m_size < str.m_size)
            return -1;

         for(size_t i = pos; i <= m_size - str.m_size; ++i)
         {
            size_t j = 0;
            while(m_str[i + j] == str.m_str[j] && j != str.m_size)
            {
               j++;
            }
            if(j == str.m_size)
               return i;
         }
         return -1;
         
      }
      int compare( const my_string& str ) const;                 // compares two strings
      constexpr bool contains( char ch ) const noexcept // checks if the string contains the given substring or character
      {
         for(int i{}; i < m_size; ++i)
         {
            if(ch == m_str[i])
               return true;
         }
         return false;
      }

      constexpr bool contains( const my_string& s ) const       // checks if the string contains the given substring or character
      {
         return 1 + find(s);
      }
   


};

my_string operator+(const char*, const my_string&); //concatenates two strings

std::ostream& operator<<(std::ostream& os, const my_string&); // performs stream output on strings
std::istream& operator>>(std::istream& is, my_string&);       // performs stream input  on strings






#endif
