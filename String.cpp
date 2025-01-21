#include "String.hpp"
#include <iostream>


my_string::my_string() : m_capacity(20), m_size(0){
   m_str = new char[m_capacity];
}

my_string::my_string( const my_string& other ): m_capacity(other.m_capacity), m_size(other.m_size){
  m_str = new char[m_capacity];

  for(size_t i{}; i < m_size; ++i){
   m_str[i] = other.m_str[i];
  }
}

my_string::my_string( const char* rhv ){
   size_t length = 0;
   for( ; rhv[length]; ++length ) //count length of rhv

   m_capacity = length + 1;
   m_size = length;
   m_str = new char[length];

   for(int i{}; i < m_size; ++i){
      m_str[i] = rhv[i];
   }

}

my_string::my_string( my_string&& rhv ): m_capacity(rhv.m_capacity) , m_size(rhv.m_size) , m_str(rhv.m_str){
   rhv.m_str = nullptr;
}

my_string::~my_string(){  
   clear();
}

 
my_string& my_string::operator=( const my_string& other ){
   if(this == &other){
      return *this;
   }

   delete[] m_str;

   m_capacity = other.m_capacity;
   m_size = other.m_size;
   m_str = new char[m_capacity];

   for(size_t i{}; i < m_size ; ++i){
      m_str[i] = other.m_str[i];
   }

   return *this;
}

my_string& my_string::operator=( const char* rhv ){
   size_t length{};
   for( ; rhv[length]; ++length )

   delete[] m_str;

   m_capacity = length + 1;
   m_size = length;
   m_str = new char[m_capacity];

   for(int i{}; i < m_size; ++i){
      m_str[i] = rhv[i];
   }

   return *this;
}

my_string& my_string::operator=( my_string&& other ){
   delete[] m_str;

   m_capacity = other.m_capacity;
   m_size = other.m_size;
   m_str = other.m_str;

   other.m_str = nullptr;

   return *this;
}

my_string my_string::operator+( const my_string& other){
   my_string tmp;
   tmp.m_size = m_size + other.m_size;
	tmp.m_capacity = m_capacity + other.m_capacity;
   tmp.m_str = new char[tmp.m_capacity];

   for(size_t i{}; i < m_size; ++i){
      tmp.m_str[i] = m_str[i];
   }

   for(size_t i{}; i < other.m_size; ++i ){
      tmp.m_str[m_size + i] = other.m_str[i];
   }

   return tmp;
}

my_string my_string::operator+( const char* rhv ){
   return *this + my_string(rhv);
}

my_string& my_string::operator+=( const my_string& other ){
   *this = *this + other;
   return *this;
}

my_string& my_string::operator+=( const char* rhv ){
   *this = *this + rhv;
   return *this;
}

char& my_string::operator[]( size_t index){
   if(index >= m_size){
      throw std::invalid_argument("INDEX OUT OF RANGE!");
   }
   return m_str[index];
}


size_t my_string::size() const{
   return m_size;
}

bool my_string::empty() const{
   return !m_size;
}

void my_string::reserve( size_t new_capacity){
   if(new_capacity > m_capacity){
      char* tmp = new char[new_capacity];
      
      for(int i{}; i < m_size; ++i){
          tmp[i] = m_str[i];
      }
  
      delete[] m_str;
      m_str = tmp;
      m_capacity = new_capacity;
   }
}

size_t my_string::capacity() const{
   return m_capacity;
}

void my_string::shrink_to_fit(){
   if(m_size < m_capacity){

      char* new_str = new char[m_size];
      for(int i{}; i < m_size; ++i){
         new_str[i] = this->m_str[i]; 
      }

      delete[] m_str;
      m_str = new_str;
      m_capacity = m_size;
   }
}

char* my_string::begin(){
   return m_str;
}

const char* my_string::begin() const{
   return m_str;
}

char* my_string::end(){
   return m_str + m_size;
}

void my_string::clear() noexcept{
   delete[] m_str;
   m_str = nullptr;
   m_size = 0;
   m_capacity = 0;
}

my_string& my_string::insert( size_t index, size_t count, char ch ){
    if (index > m_size) {
        std::cerr << "Error: index out of bound!\n";
        return *this;
    }
    if (m_size + count > m_capacity) {
        resize(m_size + count , ' ');
    }

    for (size_t i = m_size; i > index; --i) {
        m_str[i + count - 1] = m_str[i - 1];
    }

    for (size_t i = 0; i < count; ++i) {
        m_str[index + i] = ch;
    }

    m_size += count;
    m_str[m_size] = '\0'; 
    return *this;
}

my_string& my_string::insert( size_t index, const char* s ){
   if(index > m_size){
      std::cerr << "Error: index out of bound!\n";
      return *this;
   }

   m_size = index;
   *this += s;
   return *this;

}

my_string& my_string::insert( size_t index, const char* s, size_t count ){
   if(index > m_size){
      std::cerr << "Error: index out of bound!\n";
      return *this;
   }

   m_size = index;
   for(size_t i{}; i < count; ++i){
      push_back(s[i]);
   }
   return *this;
}

my_string& my_string::insert( size_t index, const my_string& str ){
    if(index > m_size){
      std::cerr << "Error: index out of bound!\n";
      return *this;
   }

    m_size = index;
    *this += str;
    return *this;

}

void my_string::push_back(char ch){
   if(m_size == m_capacity){
      this->reserve(2 * m_capacity);
   }
   m_str[m_size] = ch;
   ++m_size;
}


void my_string::pop_back(){
   if(!this->empty()){
      m_str[m_size - 1] = '\0';
      --m_size;
   }
}

void my_string::resize( size_t count , char ch = ' ' ){
  if(count < m_size){
     for(size_t i = count; i < m_size; ++i){
        m_str[i] = '\0';
     }

     m_size = count;
  }
  while(m_size != count){
     push_back(ch);
  }
}

void my_string::swap( my_string& other ) noexcept{
   char* tmp = m_str;
   m_str = other.m_str;
   other.m_str = tmp;

   m_size ^= other.m_size;
   other.m_size ^= m_size;
   m_size ^= other.m_size;

   m_capacity ^= other.m_capacity;
   other.m_capacity ^= m_capacity;
   m_capacity ^= other.m_capacity;
}

int my_string::compare( const my_string& other) const{
   if(m_size >  other.m_size){
      return 1;
   }else if(m_size < other.m_size){
      return -1;
   }

   for(size_t i{}; i < m_size; ++i){
      if(m_str[i] > other.m_str[i]){
         return 1;
      }else if(m_str[i] < other.m_str[i]){
         return -1;
      }
   }
   return 0;
}

my_string operator+(const char* str1, const my_string& str2){
   my_string tmp(str1);
   tmp += str2;
   return tmp;
}

std::ostream& operator<<(std::ostream& os, const my_string& str){
   os << str.begin();
   return os;
}

std::istream& operator>>(std::istream& is, my_string& str){
   char buffer[1024];
   is >> buffer;

   str.resize(0,'\0');
 
   
    size_t i = 0;
   while(buffer[i]){
      str.push_back(buffer[i]);
      ++i;
   }
   
   return is;
}


