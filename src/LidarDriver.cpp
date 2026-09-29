#include "../include/LidarDriver.h"

//costruttori
LidarDriver::LidarDriver(){
   num_readings = 181;
   resolution = 1;
   head = 0;
   tail = 0;
   buffer.resize(BUFFER_DIM, std::vector<double>(num_readings, 0));
}

LidarDriver::LidarDriver(double res){
   resolution = res;
   head = 0;
   tail = 0;
   if (res < 0.1 || res > 1.0){
      throw std::invalid_argument("Risoluzione angolare fuori dal range");
   }
   else{
      num_readings = static_cast<int>(180/resolution + 1);
      buffer.resize(BUFFER_DIM, std::vector<double>(num_readings, 0));
   }
}

//funzione new_scan che aggiunge una scansione al buffer
void LidarDriver::new_scan(std::vector<double>& scan) {
   std::vector<double> newScan(num_readings, 0.0);
   for (int i = 0; i < scan.size(); i++) {
      newScan[i] = scan[i];
   }
   buffer[head] = scan; //le scansioni vecchie vengono sovrascritte quando
                        //il buffer e' pieno
   head = (head + 1) % BUFFER_DIM; //aggiornamento dell'indice in testa alla coda

   if (buf_size < BUFFER_DIM) {
      buf_size++;
   }
   else {
      tail = (tail + 1) % BUFFER_DIM; //fa in modo che l'indice torni a zero
                                      //la coda si sposta all'inizio del buffer sovrascrivendo
                                      //la scansione iniziale
   }
}

//funzione get_scan che restituisce e rimuove la scansione piu' vecchia    
std::vector<double> LidarDriver::get_scan() {
   if (buffer.empty()) {
      throw std::runtime_error("Attenzione, il buffer e' vuoto");
   }

   int oldest=(tail+buf_size-1)% BUFFER_DIM; //indice scansione piu vecchia
   //(tail -1) indica la scansione piu' vecchia e + buf_size mi permette di mantenere la circolaritā 

   std::vector<double> oldest_scan=buffer[oldest];

   buffer[oldest].clear();

   return oldest_scan;
}

//funzione clear_buffer che elimina senza restituire tutte le scansioni salvate
void LidarDriver::clear_buffer(){
   head = 0;
   tail = 0;
   buf_size = 0;
   buffer.clear();
}

//funzione get_distance che restituisce la distanza per un angolo dell'ultima scansione
double LidarDriver::get_distance(double angle) {
   if (buf_size == 0) {
      throw std::invalid_argument("Il buffer e' vuoto!");
   }
   if (angle < 0.0 || angle > 180.0) {
      throw std::invalid_argument("Angolo fuori dal range [0-180]");
   }
   std::vector<double>& lastScan = buffer[(head -1 +BUFFER_DIM) % BUFFER_DIM];
   //gestione circolare dell'array, punta all'elemento precedente rispetto a head
   int index = static_cast<int>(std::round(angle/resolution)); 
   //trova l'indice arrotondando alla lettura piu' vicina
   
   //controllo se sono entro i limiti di num_readings
   if (index < 0) {
      index = 0;
   } else if (index >= num_readings) {
      index = num_readings; 
   }
   return lastScan[index];
}

//overloading dell'operator <<
std::ostream& operator<<(std::ostream& os, LidarDriver& driver) {
   if (driver.buf_size == 0) {   //controllo che buffer non sia vuoto
      os << "Il buffer e' vuoto!";
      return os;
   }
   std::vector<double>& lastScan = driver.buffer[(driver.head - 1 + driver.BUFFER_DIM) % driver.BUFFER_DIM];   //vettore dell'ultima scansione salvata
   //stampa del vettore
   os << "[ ";
   for (int i = 0; i < driver.num_readings; i++) {
      os << lastScan[i] << " ";
   }
   os << "]";
   return os;
}

