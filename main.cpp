#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <vector>

struct series{
    std::string name;
    int nTotalVolumes;
    int nTotalConsumedVolumes;
};

struct SeriesTracker{
   std::vector<series> vSeries;
};

void add_new_anime(SeriesTracker *s){

    std::string series_name;
    int totalVolumes, VolumesRead;

    std::cout << "Enter the name of the series:" << std::endl;
    std::cin >> series_name;

    std::cout << "Total number of volumes:" << std::endl;
    std::cin >> totalVolumes;

    std::cout << "Number of volumes read:" << std::endl;
    std::cin >> VolumesRead;

    series new_series = {
        .name = series_name,
        .nTotalVolumes = totalVolumes,
        .nTotalConsumedVolumes = VolumesRead
    };

    s->vSeries.push_back(new_series);

}

void display_all_series(SeriesTracker *st){

    std::cout << "Series progress" << std::endl;
    for (series s : st->vSeries)
    {
        int bar_length = 20; 

        int num_stars = (s.nTotalConsumedVolumes * bar_length) / s.nTotalVolumes;

        int num_bars = bar_length - num_stars;

        float progress = ((float)s.nTotalConsumedVolumes / s.nTotalVolumes);

        float progress_percent  = progress * 100;

        std::cout << s.name << std::endl;
        std::cout << "\t" << "[";

        for (int i = 0; i < num_stars; i++)
        {
            std::cout << "*";
        }

        for (int j = 0; j < num_bars; j++)
        {
            std::cout << "|";
        }

        std::cout << "]" << " Progress: " << std::floor(progress_percent) << "%" << std::endl;
    }
    
}

void load_from_file(SeriesTracker *st){
    std::ifstream csv_file("series_data.csv");

    std::vector<std::string> row;
    std::string line, word;

    while (getline(csv_file, line))
    {
        row.clear();
        std::stringstream s(line);

        while (getline(s, word, ','))
        {
            row.push_back(word);
        }

        int total_volumes = std::stoi(row[1]);
        int volumes_read  = std::stoi(row[2]);

        series new_series = {
            .name = row[0],
            .nTotalVolumes = total_volumes,
            .nTotalConsumedVolumes = volumes_read
        };

        st->vSeries.push_back(new_series);  
    }
    
    csv_file.close();
}

void edit_series_info(SeriesTracker *st){
    int count = 1, choice;

    for (series serie : st->vSeries)
    {
        std::cout << count << " " << serie.name << std::endl;
        count++;
    }

    std::cout << "\n";
    std::cout << "Choose index of series you want to edit" << std::endl;

    std::cin >> choice;

    std::cout << "\n";
    std::string print_name = st->vSeries[choice - 1].name;
    std::cout << "Altering" <<  print_name << std::endl;
    std::cout << "\n";
    
    std::cout << "New name" << std::endl;
    std::cin >> st->vSeries[choice - 1].name;

    std::cout << "Updated Volume Count" << std::endl;
    std::cin >> st->vSeries[choice - 1].nTotalVolumes;

    std::cout << "Updated Volumes Read" << std::endl;
    std::cin >> st->vSeries[choice - 1].nTotalConsumedVolumes;
}


void delete_series(SeriesTracker *st){
    int count = 1, choice;

    for (series serie : st->vSeries)
    {
        std::cout << count << " " << serie.name << std::endl;
        count++;
    }

    std::cout << "\n";
    std::cout << "Choose index of series you want to edit" << std::endl;

    std::cin >> choice;

    int index = choice - 1;
    st->vSeries.erase(st->vSeries.begin() + index);
}

int main(){

    SeriesTracker st;
    load_from_file(&st);

    bool bRunProgram = true;
    int choice;
    std::cout << "Welcome to your personal Series Tracker" << std::endl;
    while (bRunProgram)
    {

        std::cout<< "Choose an option:"<< std::endl;
        std::cout<<"\n";
        std::cout<<"1. Add new Series" << std::endl;
        std::cout<<"2. Display All Series" << std::endl;
        std::cout<<"3. Update Series info" << std::endl;
        std::cout<<"4. Delete Series" << std::endl;
        std::cout<<"5. Quit program" << std::endl;
        std::cout<<"\n";

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            add_new_anime(&st);
            break;
        case 2:
            display_all_series(&st);
            break;
        case 3:
            edit_series_info(&st);
            break;
        case 4:
            delete_series(&st);
            break;
        case 5:
            bRunProgram = false;
            std::cout << "Program Closing ..." << std::endl;
            break;
        default:
            std::cout << "Program expects number between 1 - 5" << std::endl;
            std::cout << "Corresponding to menu option" << std::endl; 
            break;
        }
    }

    std::ofstream csv_file("series_data.csv");

    for (series serie : st.vSeries)
    {
        csv_file << serie.name << "," << serie.nTotalVolumes << "," << serie.nTotalConsumedVolumes << "\n";
    }
    csv_file.close();
    
}