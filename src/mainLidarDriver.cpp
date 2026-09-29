#include <vector>
#include <iostream>
#include "../include/LidarDriver.h"

int main(){
   LidarDriver ld1 = LidarDriver();
   std::cout << "Creazione primo oggetto:\n" << ld1 << "\n";

   double res1 = 0.5;
   LidarDriver ld2 = LidarDriver(res1);
   std::cout << "Creazione secondo oggetto (quello usato qui):\n" <<ld2 << "\n";
   
   /*double res2 = 5.0;
   LidarDriver ld3 = LidarDriver(res2);
   std::cout << "Creazione terzo oggetto:\n" << ld3;*/
   
   std::cout << "Inserimento della scansione {1.2, 4.5, 4.3, 5.6, 9.1} \n";
   std::vector<double> scan1 = {1.2, 4.5, 4.3, 5.6, 9.1};
   ld2.new_scan(scan1);
   std::cout << "Ultima scansione:\n" << ld2 << "\n";
   
   std::cout << "Inserimento della scansione {9.1, 5.6, 4.3, 4.5, 1.2} \n";
   std::vector<double> scan2 = {9.1, 5.6, 4.3, 4.5, 1.2};
   ld2.new_scan(scan2);
   std::cout << "Ultima scansione:\n" << ld2 << "\n";
   ld2.get_scan();
   std::cout << "Rimozione della scansione più vecchia\n";

   double angle = 1.5;
   double distance = ld2.get_distance(angle);
   std::cout << "Distanza per un angolo di 1.5 gradi dell'ultima scansione inserita: ";
   std::cout << distance << "\n";
   
   std::cout << "Svuoto tutto il buffer \n";
   ld2.clear_buffer();
   std::cout << ld2 << "\n";
   
}
