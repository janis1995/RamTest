// RamTest.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <chrono>

#define RAM_SIZE 1000000000
#define GIGS_TO_WRITE 32
#define GIGS_TO_READ 32

static void write_test();
static void read_test();

char* ptr = nullptr;

int main()
{
   std::cout << "Ram test started" << std::endl;

   ptr = new char[RAM_SIZE];

   write_test();
   read_test();

   delete [] ptr;
   
}

static void write_test()
{
   //Write a huge amount of memory
  
   auto t_start = std::chrono::high_resolution_clock::now();
   
   for (int j = 0; j < GIGS_TO_WRITE; j++)
   {
      memset(ptr, 0x12, RAM_SIZE);
   }
   auto t_end = std::chrono::high_resolution_clock::now();
   double duration = std::chrono::duration<double, std::milli>(t_end - t_start).count();
   std::cout << "Time to write:" << duration << "ms" << std::endl;
   std::cout << "Write speed:" << GIGS_TO_WRITE / (duration / 1000) << "GB/s" << std::endl;
}

static void read_test()
{
   //Read a huge amount of memory

   auto t_start = std::chrono::high_resolution_clock::now();
   long* ptr_fast = (long*)ptr;
   
   for (int j = 0; j < GIGS_TO_READ; j++)
   {
      for (int i = 0; i < RAM_SIZE / 8; i += 8)
      {
         long buf = ptr_fast[i];
      }
   }
   auto t_end = std::chrono::high_resolution_clock::now();

   double duration = std::chrono::duration<double, std::milli>(t_end - t_start).count();
   std::cout << "Time to Read:" << duration << "ms" << std::endl;
   std::cout << "Read speed:" << GIGS_TO_READ / (duration / 1000) << "GB/s" << std::endl;
}
