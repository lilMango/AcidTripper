#include "fps.h"

void Fps::reset(){ 
  frames = 0; 
  time(&startTime); 
} 
void Fps::update(){ 
  time(&endTime); 
  double diff = difftime(endTime, startTime); 
  frames++; 
  if(diff > 1.0){ 
    // 1 second 
    std::cout << "FPS: " << frames / diff << std::endl; 
    reset(); 
  } 
} 
