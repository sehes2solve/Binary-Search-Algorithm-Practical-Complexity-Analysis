#ifndef SEARCHER_H
#define SEARCHER_H
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

template <class T>
class Searcher
{
public:
    Searcher();
    Searcher(char* file_directory)
    {
        loadData(file_directory);
    }


    void loadData(char* file_directory)
    {
        ifstream file(file_directory);
        if(file.fail())
        {
            cout << "Opening File Failed : Incorrect Directory Or File is being processing now !!!"
                 << "\nPlease try again" << endl;
        }
        else
        {
            data.clear();
            T temp;
            while(true)
            {
                file >> temp;
                if(file.fail())
                    break;
                data.push_back(temp);
            }
        }
        file.close();
    }


    int binarySearch(T quested,double& period,int& comp_num)
    {
        comp_num = 1;
        auto start = high_resolution_clock::now();
        for(int i = 0,j = data.size()-1,mid = (i+j)/2; i <= j; mid =(i+j)/2,comp_num++)
        {
            if(data[mid] == quested)
            {
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(stop-start);
                period = duration.count();
                return mid;
            }
            else if(data[mid] > quested)
                j = mid - 1;
            else
                i = mid + 1;
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop-start);
        period = duration.count();
        return -1;
    }


    int testPerformance()
    {
        char test_sample[] = "test - (1).txt";
        double bp;
        int bc , q_index;
        T quest,q_exchange;
        vector<T> temp;
        for(int i = 0; i < 8; i++)
        {
            test_sample[8] = i + 1 + '0';
            loadData(test_sample);
            avg_periods[2*(i)] = 0;
            avg_comp_nums[2*(i)] = 0;

            // 100 search for average case of searching
            // stored in even number of array
            for(int j = 0; j < 100000; j++,avg_periods[2*(i)] += bp,avg_comp_nums[2*(i)] += bc)
            {
                quest = data[rand()%((i+1)*10000-1)];
                binarySearch(quest,bp,bc);
            }
            avg_periods[2*(i)+1] = 0;
            avg_comp_nums[2*(i)+1] = 0;
            // 100 search for worst case of searching
            // stored in odd number of array
            for(int j = 0; j < 100000; j++,avg_periods[2*(i)+1] += bp,avg_comp_nums[2*(i)+1] += bc)
            {
                /*q_index = rand()%((i+1)*10000-1);
                quest = data[q_index];
                q_exchange = 'z' + char((rand() % 10) + 'a');
                swap(data[q_index],q_exchange);
                binarySearch(quest,bp,bc);
                swap(data[q_index],q_exchange);*/
                q_index = rand()%((i+1)*10000-1);
                quest = data[q_index];
                if(q_index != 0)
                    q_exchange = data[q_index-1];
                else
                    q_exchange = data[q_index+1];
                swap(data[q_index],q_exchange);
                binarySearch(quest,bp,bc);
                swap(data[q_index],q_exchange);
            }
            avg_periods[2*(i)] /= 100000;
            avg_comp_nums[2*(i)] /= 100000;
            avg_periods[2*(i)+1] /= 100000;
            avg_comp_nums[2*(i)+1] /= 100000;
        }
        double total_avg;
        for(int i = 0; i < 16; i++)
            total_avg += avg_periods[i] + avg_comp_nums[i];
        return total_avg/32;
    }


    void display_avg()
    {
        for(int i = 0; i < 8; i++)
        {

            cout << char(i + 1 + '0') << " file:\n"
                 << "avg avg-case-period :  " << avg_periods[2*i] << '\n'
                 <<  "avg avg-case-comp :  " << avg_comp_nums[2*i] << '\n'
                 << "avg worst-case-period :  " << avg_periods[2*i+1] << '\n'
                 <<  "avg worst-case-comp :  " << avg_comp_nums[2*i+1] << '\n';
        }
    }
    virtual ~Searcher()
    {
        //dtor
    }

protected:

private:
    vector<T> data;
    double avg_periods[16] = {0}, avg_comp_nums[16] = {0};

};

#endif // SEARCHER_H
//#include "src/SEARCHER.CPP"
