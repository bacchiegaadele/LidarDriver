#ifndef LIDAR_DRIVER_H
#define LIDAR_DRIVER_H

//librerie
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>

class LidarDriver {
   public:
      //costruttori
      LidarDriver();
      LidarDriver(double res);

      //funzioni
      void new_scan(std::vector<double>& scan);
      std::vector<double> get_scan();
      void clear_buffer();
      double get_distance(double ang);

      //operator <<
      friend std::ostream& operator<<(std::ostream& os, LidarDriver& driver);

   private:
      //variabili
      static constexpr int BUFFER_DIM = 10;
      int buf_size; //dimensione logica del buffer
      int num_readings; //numero di letture dentro ogni scansione
      int head; //testa del buffer
      int tail; //coda del buffer
      double resolution;
      std::vector<std::vector<double>> buffer; //buffer circolare delle scansioni
};

#endif 
