#include <iostream>
#include <fstream>
#include <ranges>
#include <algorithm>
#include <utility>
#include <string>

#include "rectangle.h"
#include "point.h"
#include "vec1D.h"
#include "scopedTimer.h"
#include "export_data.h"

using namespace std;


void generateDistribution(const int NUM_ELEMENTS, BASIC_RNG distrubutionA, BASIC_RNG distrubutionB, const std::pair<float, float>& argA, const std::pair<float, float>& argB){
    // step 1. unpack pair, first and second item in pair are the first and second argument respectively. 
    
    auto title = std::string{"Generating Distribution of size "} + std::to_string(NUM_ELEMENTS);
    Timer A(title.c_str(), UNIT::US);
    
    float paramA = argA.first;
    float paramB = argA.second;

    Vec1D a(NUM_ELEMENTS, distrubutionA, argA.first, argA.second);
    Vec1D b(NUM_ELEMENTS, distrubutionB, argB.first, argB.second);

    auto sum = a + b;
    if (sum.has_value()){
        // print out the sum of the 2 distributions.
        auto& result = sum.value();
    } else{
        std::cout << "sizes of vec1D objects are not the same " << std::endl;
    }

}


int main(){

    // Generate range to sweep across

    auto range = std::views::iota(8,16) | std::views::transform([](int x){return (1 << x);});
    
    std::pair<float, float> meanAndStdDeviationParams{30.0,50.0};
    std::pair<float, float> minAndMaxParams{10.0,100.0};

    for (auto num_elements : range){
        generateDistribution(num_elements, BASIC_RNG::GAUSSIAN, BASIC_RNG::GAUSSIAN, meanAndStdDeviationParams, minAndMaxParams);
    }

    return 0;
}


