#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <list>
#include <iterator>
#include <fstream>
#include <math.h>
#include <ctime>
#include <string>
#include <vector>
using namespace cv;

static int tflag = 0;
static double tcount[120];
int testNumber = 1;

//DIEHARD TESTS:

unsigned int roll(double number)
{
    number /= 4294967296;
    number *= 6;
    return (unsigned int)number + 1;
}
/*

void craps(std::list<int> const& list)
{
    std::ofstream distribution("distribution.txt");
    
    double number = 0;
    auto it = list.cbegin();
    double p = 244.0 / 495.0;
    unsigned int throws, tries, wins;
    long int results[21];
    double normalDistribution[21];
    double point;

    double sum = 1.0 / 3.0;
    normalDistribution[0] = sum;
    for (int i = 1; i < 20; i++)
    {
        normalDistribution[i] = (27.0 * pow(27.0 / 36.0, i - 1) + 40 * pow(13.0 / 18.0, i - 1) + 55.0 * pow(25.0 / 36.0, i - 1)) / 648.0;
        sum += normalDistribution[i];
    }
    normalDistribution[20] = 1.0 - sum;
     
    for (int i = 0; i < 21; i++)
    {
        normalDistribution[i] *= 200000;
    }
    
    for ( int i = 0; i <= 20; i++)
    {
        results[i] = 0;
    }
    wins = 0;
    
    for (int j = 0; j < 200000; j++)
    {
        tries = 0;
        while (1)
        {
            point = 0;
            for (int z = 0; z < 2; z++)
            {
                    for (int i = 31; i >= 0; i--)
                    {
                        number += *it * pow(2, i);
                        it++;
                        if (it == list.cend())
                            it = list.cbegin();
                    }   
                point += roll(number);
                number = 0;
            }
            if (point == 7 || point == 11)
            {
                wins++;
                results[tries]++;
                break;
            }
            else if (point == 2 || point == 3 || point == 12)
            {
                results[tries]++;
                break;
            }
            else
            {
                if (tries < 20)
                    tries++;   
            }
        }
    }
    std::ofstream result("result_craps.txt", std::ios_base::app);
    result << std::endl << "test " << testNumber << ":" << std::endl;
    for (int i = 0; i <= 20; i++)
    {
        result << results[i] << std::endl;
    }
    if (testNumber == 1)
    for (int i = 0; i < 21; i++)
    {
            distribution << normalDistribution[i] << std::endl;
    }
    result << wins << std::endl;
    result.close();
    distribution.close();
}
*/
void craps(std::list<int> const& list)
{
    std::ofstream distribution("distribution_craps.txt", std::ios_base::app);
    
    double number = 0;
    auto it = list.cbegin();
    double p = 244.0 / 495.0;
    unsigned int throws, tries, wins;
    long int results[21];
    double normalDistribution[21];
    double point;
    double prevPoint = 0;

    double sum = 1.0 / 3.0;
    normalDistribution[0] = sum;
    for (int i = 1; i < 20; i++)
    {
        normalDistribution[i] = (27.0 * pow(27.0 / 36.0, i - 1) + 40 * pow(13.0 / 18.0, i - 1) + 55.0 * pow(25.0 / 36.0, i - 1)) / 648.0;
        sum += normalDistribution[i];
    }
    normalDistribution[20] = 1.0 - sum;
     
    for (int i = 0; i < 21; i++)
    {
        normalDistribution[i] *= 200000;
    }
    
    for ( int i = 0; i <= 20; i++)
    {
        results[i] = 0;
    }
    wins = 0;
    
    for (int j = 0; j < 200000; j++)
    {
        tries = 0;
        prevPoint = 0;
        for (int z = 0; z < 2; z++)
            {
                    for (int i = 31; i >= 0; i--)
                    {
                        number += *it * pow(2, i);
                        it++;
                        if (it == list.cend())
                            it = list.cbegin();
                    }   
                prevPoint += roll(number);
                number = 0;
            }
       if (prevPoint == 7 || prevPoint == 11)
            {
                wins++;
                results[tries]++;
               
            }
       else if (prevPoint == 2 || prevPoint == 3 || prevPoint == 12)
            {
                results[tries]++;
                
            }
       else
        while (1)
        {
            if (tries < 20)
               tries++; 
            point = 0;
            for (int z = 0; z < 2; z++)
            {
                    for (int i = 31; i >= 0; i--)
                    {
                        number += *it * pow(2, i);
                        it++;
                        if (it == list.cend())
                            it = list.cbegin();
                    }   
                point += roll(number);
                number = 0;
            }
            if(point == 7){
            results[tries]++;
	        break;
            } 
            else if(prevPoint == point){
            results[tries]++;
	        wins++;
	        break;
            }
        }
    }
    std::ofstream result("result_craps.txt", std::ios_base::app);
    
    for (int i = 0; i <= 20; i++)
    {
        result << "test " << testNumber << ": ";
        result << results[i] << std::endl;
    }
    if (testNumber == 1)
    for (int i = 0; i < 21; i++)
    {
            distribution << "test " << testNumber << ": ";
            distribution << normalDistribution[i] << std::endl;
    }
    result << "test " << testNumber << ": ";
    result << wins << std::endl;
    result.close();
    distribution.close();
}

void count_the_ones(std::list<int> const& list, std::string fileName, std::string distributionName, int letters)
{
    std::ofstream result(fileName, std::ios_base::app);
    std::ofstream distribution(distributionName, std::ios_base::app);
    auto it = list.cbegin();
    double *probability;
    probability = new double[letters];
    double tmpy = 1;
    std::string word;
    std::vector<std::pair<std::string, int>> words;
    int letter;
    bool check;

    for (int i = 0; i < letters; i++)
    {
        letter = 0;
        for (int j = 0; j < 8; j++)
        {
            if (*it == 1)
                letter++;
            it++;
            if (it == list.cend())
                it = list.cbegin();
        }
        if (letter < 3)
        {
            word += 'A';
            probability[i] = 0.14453125;
        }
        else if (letter == 3)
        {
            word += 'B';
            probability[i] = 0.21875;
        }
        else if (letter == 4)
        {
            word += 'C';
            probability[i] = 0.2734375;
        }  
        else if (letter == 5)
        {
            word += 'D';
            probability[i] = 0.21875;
        }
        else
        {
            word += 'E';
            probability[i] = 0.14453125;
        }
    }

    for (int z = 0; z < 256000-1; z++)
    {  
        check = 0;
        tmpy = 1;
        if(words.size() == 0)
        {
            words.push_back(std::pair<std::string, int>(word, 1));
            for (int z = 0; z < letters; z++)
                {
                    //std::cout << probability[z] << std::endl;
                    tmpy *= probability[z];
                }
                distribution << "test " << testNumber << ": ";
                distribution << word << " " << tmpy << std::endl;
        }
        else
        {
            for (int i = 0; i < words.size(); i++)
            {
                if (words[i].first == word)
                {
                    words[i].second++;
                    check = 1;
                }
            }
            if(check == 0)
            {
                words.push_back(std::pair<std::string, int>(word, 1));
                for (int z = 0; z < letters; z++)
                {
                    //std::cout << probability[z] << std::endl;
                    tmpy *= probability[z];
                }
                distribution << "test " << testNumber << ": ";
                distribution << word << " " << tmpy << std::endl;
            }  
        }
        for(int i = 0; i < letters-1; i++)
        {
            word[i] = word[i + 1];
            probability[i] = probability[i + 1];
        }

        letter = 0;
        for (int j = 0; j < 8; j++)
        {
            if (*it == 1)
                letter++;
            it++;
            if (it == list.cend())
                it = list.cbegin();
        }
        if (letter < 3)
        {
            word[letters - 1] = 'A';
            probability[letters - 1] = 0.14453125;
        }
        else if (letter == 3)
        {
            word[letters - 1] = 'B';
            probability[letters - 1] = 0.21875;
        }
        else if (letter == 4)
        {
            word[letters - 1] = 'C';
            probability[letters - 1] = 0.2734375;
        }
        else if (letter == 5)
        {
            word[letters - 1] = 'D';
            probability[letters - 1] = 0.21875;
        }
        else
        {
            word[letters - 1] = 'E';
            probability[letters - 1] = 0.14453125;
        }
    }
    
    for (int i = 0; i < words.size(); i++)
    {
        result << "test " << testNumber << ": ";
        result << words[i].first << " " << words[i].second << std::endl;
    }
    delete probability;
}


void bit_stream(std::list<int> const& list, int n = 20)
{
    std::ofstream result("result_bitStream.txt", std::ios_base::app);
    std::vector<uint> words;
    uint window = 0;
    bool check;
    auto it = list.cbegin();
    uint mask = 0x0007FFFF; //mam bład /chyba, zw

    while (it != list.cend())
    {   
        window &= mask;
        if (!words.size())
        {  
            for (int i = 0; i < n; i++)
            {
                window <<= 1;
                if (*it == 1)
                    window += 1;
                
                     // window = window << 1;
                it++;
                if (it == list.cend())
                    it = list.cbegin();
            }
            words.push_back(window);
        }
        else
        {
            window <<= 1;
            if (*it == 1)
                window += 1;
            it++;
            
            words.push_back(window);
        }
    }
    
    result << "Test: " << testNumber << " ";
 
    int counter = 0;
    std::sort(words.begin(), words.end());
    auto last = std::unique(words.begin(), words.end());
    words.erase(last, words.end());
    for (auto i = words.begin(); i != words.end(); i++)
    {
        //result << *i << std::endl;
        counter++;
    }
    result << pow(2, 20) - counter << std::endl;
}

//DIEHARD end

//RNG

void print(std::list<int> const& list)
{
    for (auto it = list.cbegin(); it != list.cend(); it++)
    {
        std::cout << *it << std::endl;
    }
}

void save_to_file(std::list<int> const& list, int x)
{
    std::ofstream file("wynik.txt");
    for (auto it = list.cbegin(); it != list.cend(); it++)
    {
        file << *it << std::endl;
        if (x == 1)
            break;
        x--;
    }
    file.close();
}

int pobierz(std::list<int>& list, int el)
{
    int tmp{ 0 };
    for (auto it = list.cbegin(); it != list.cend(); it++)
    {
        if (el == tmp)
            return *it;
        tmp++;
    }

}

void calc(std::list<int> const& list)
{
    std::ofstream file("losowe_liczby.txt");
    int number = 0, temp = 7, bit = 0;
    for (auto it = list.cbegin(); it != list.cend(); it++)
    {
        bit = *it;
        //std::cout << bit;
        bit <<= temp;
        number = number | bit;
        temp--;
        if (temp < 0)
        {
            temp = 7;
            file << number << std::endl;
            //std::cout << std::endl << number << std::endl;
            number = 0;
            //  break;
        }
    }
    file.close();
}

int flip(int num)
{
    if (num == 1)
        return 0;
    else
        return 1;
}

void TRNG(char nr, int bitAmount)
{
    clock_t start;
    std::list<int> subList{ };
    std::list<int> finalList{ };
    int frameNum = 0;
    int size{ 16 }; //podac 

    Point3_<uchar>* p;
    //taking photo
    VideoCapture camera(0);
    camera.set(CAP_PROP_FRAME_WIDTH, 1920);
    camera.set(CAP_PROP_FRAME_HEIGHT, 1080);
    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return;
    }

    Mat img;
    do
    {
        //start = clock();
        for (int i = 0; i < 4; i++)
        {
            camera >> img;
            if (img.empty())
            {
                std::cout << "Could not read the image " << std::endl;
                return;
            }

            frameNum++;

            for (int i = 0; i < img.rows; i++)
            {
                for (int j = 0; j < img.cols; j++)
                {
                    p = img.ptr<Point3_<uchar> >(i, j);
                    int siatka = 0x0001;

                    if ((int)p->x > 1 && (int)p->x < 254)
                    {
                        if (frameNum % 2 == 0)
                            subList.push_back(flip(siatka & (int)p->x));
                        else
                            subList.push_back(siatka & (int)p->x);
                    }

                    if ((int)p->y > 1 && (int)p->y < 254)
                    {
                        if (frameNum % 2 == 0)
                            subList.push_back(flip(siatka & (int)p->y));
                        else
                            subList.push_back(siatka & (int)p->y);
                    }

                    if ((int)p->z > 1 && (int)p->z < 254)
                    {
                        if (frameNum % 2 == 0)
                            subList.push_back(flip(siatka & (int)p->z));
                        else
                            subList.push_back(siatka & (int)p->z);
                    }
                }
            }
        }
        //std::cout << (clock() - start) * 0.001 << std::endl;
    } while (subList.size() < bitAmount);

    std::cout << "Wykonuje sie test numer: " << testNumber << std::endl;

    auto it = subList.cbegin();
    size = ceil(sqrt(bitAmount));
    //tworzenie tablicy
    int** tab{ new int* [size] };
    for (int i = 0; i < size; i++)
    {
        tab[i] = new int[size];
    }

    int z{ 0 };
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            tab[j][i] = *it;
            it++;
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            finalList.push_back(tab[i][j]);
        }
    }

    for (int i = 0; i < size; i++)
    {
        delete[] tab[i];
    }
    delete[] tab;
    //****************************

    if (nr == 'a')
        craps(finalList);
    if (nr == 'b')
    {
        count_the_ones(finalList, "results_5_letters.txt", "distribution_5_letters.txt", 5);
        count_the_ones(finalList, "results_4_letters.txt", "distribution_4_letters.txt", 4);
    }
    if (nr == 'c')
        bit_stream(finalList, 20);
    if (nr == 'd')
        calc(finalList);
    if (nr == 'd')
        save_to_file(finalList, bitAmount);
}

//RNG end

int main()
{
    char nr;
    int bit;
    clock_t start;
    std::cout << "Pick test: " << std::endl;
    std::cout << "a - Craps" << std::endl;
    std::cout << "b - Count the ones" << std::endl;
    std::cout << "c - Bit_stream" << std::endl;
    std::cout << "d - Just random numbers(8 bit values)" << std::endl;
    std::cout << "e - Just random numbers(just bits)" << std::endl;
    std::cin >> nr;
    std::cout << std::endl << "Podaj pozadana liczbe bitow:" << " ";
    std::cin >> bit;
    for (int i = 0; i < 1; i++)
    {
        start = clock();
        TRNG(nr, bit);
        testNumber++;
        std::cout << "czas testu: " << (clock() - start) * 0.001<< std::endl;
    }
    return 0;
}