#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <map>

//morse to alphabet
void decoder_car(std::string Code)  {
	
	std::string msg = "None";
	
	if (Code == ".-")  msg = "A";
	
	if (Code == "-...")  msg = "B";
	
	if (Code == "-.-.")  msg = "C";
	
	if (Code == "-..")  msg = "D";
	
	if (Code == ".")  msg = "E";
	
	if (Code == "..-.")  msg = "F";
	
	if (Code == "--.")  msg = "G";
	
	if (Code == "....")  msg = "H";
	
	if (Code == "..")  msg = "I";
	
	if (Code == ".---")  msg = "J";
	
	if (Code == "-.-")  msg = "K";
	
	if (Code == ".-..")  msg = "L";
	
	if (Code == "--")  msg = "M";
	
	if (Code == "-.")  msg = "N";
	
	if (Code == "---")  msg = "O";
	
	if (Code == ".--.")  msg = "P";
	
	if (Code == "--.-")  msg = "Q";
	
	if (Code == ".-.")  msg = "R";
	
	if (Code == "...")  msg = "S";
	
	if (Code == "-")  msg = "T";
	
	if (Code == "..-")  msg = "U";
	
	if (Code == "...-")  msg = "V";
	
	if (Code == ".--")  msg = "W";
	
	if (Code == "-..-")  msg = "X";
	
	if (Code == "-.--")  msg = "Y";
	
	if (Code == "--..")  msg = "Z";
	
	if (Code ==  "/") 	msg = " ";

	if (Code == ".----") msg = "1";
	
	if (Code == "..---") msg = "2";
	
	if (Code == "...--") msg = "3";
	
	if (Code == "....-") msg = "4";
	
	if (Code == ".....") msg = "5";
	
	if (Code == "-....") msg = "6";
	
	if (Code == "--...") msg = "7";
	
	if (Code == "---..") msg = "8";
	
	if (Code == "----.") msg = "9";
	
	if (Code == "-----") msg = "0";
	
	if(msg == "None"){
        throw std::invalid_argument("(" + Code +
                              "): ce caractere ne correspond pas à un caractère morse");
    }
    std::cout<<msg;
}

//alphabet to morse
std::map<char, std::string> morseCodeMap = {
    {'a', ".-"},
    {'b', "-..."},
    {'c', "-.-."},
    {'d', "-.."},
    {'e', "."},
    {'f', "..-."},
    {'g', "--."},
    {'h', "...."},
    {'i', ".."},
    {'j', ".---"},
    {'k', "-.-"},
    {'l', ".-.."},
    {'m', "--"},
    {'n', "-."},
    {'o', "---"},
    {'p', ".--."},
    {'q', "--.-"},
    {'r', ".-."},
    {'s', "..."},
    {'t', "-"},
    {'u', "..-"},
    {'v', "...-"},
    {'w', ".--"},
    {'x', "-..-"},
    {'y', "-.--"},
    {'z', "--.."},
    {'A', ".-"},
    {'B', "-..."},
    {'C', "-.-."},
    {'D', "-.."},
    {'E', "."},
    {'F', "..-."},
    {'G', "--."},
    {'H', "...."},
    {'I', ".."},
    {'J', ".---"},
    {'K', "-.-"},
    {'L', ".-.."},
    {'M', "--"},
    {'N', "-."},
    {'O', "---"},
    {'P', ".--."},
    {'Q', "--.-"},
    {'R', ".-."},
    {'S', "..."},
    {'T', "-"},
    {'U', "..-"},
    {'V', "...-"},
    {'W', ".--"},
    {'X', "-..-"},
    {'Y', "-.--"},
    {'Z', "--.."},
    {'1', ".----"},
    {'2', "..---"},
    {'3', "...--"},
    {'4', "....-"},
    {'5', "....."},
    {'6', "-...."},
    {'7', "--..."},
    {'8', "---.."},
    {'9', "----."},
    {'0', "-----"},
    {' ', "/"},
};

// constantes utilies pour les fichier wav
typedef struct header_file
{
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate;
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;
} header;

typedef struct header_file* header_p;

//Ecriture d'un int en binaire dans un fichier wav
void write_as_bytes(std::ofstream &file, int value, int byte_size)
{
    file.write(reinterpret_cast<const char*>(&value), byte_size);
}

void decoder_msg(){
    std::string filePath;
    std::cout<<"\nChemin de l'audio à décoder (avec .wav) :\n";

    getline(std::cin >> std::ws, filePath);

    FILE * infile = fopen(filePath.c_str(),"rb");	
	int BUFSIZE = 512;					
	short int buff16[BUFSIZE];
	header_p meta = (header_p)malloc(sizeof(header));	
	std::vector<short int> morseSignal; //signal brut
	int nb;	
	int currentCount = 0; //compteur de la longueur d'un element du signal
	bool isValue = true; //vrai si le signal est non nul à un moment donné
	std::string sentence = ""; //message en francais


	if (infile)
	{
		/// Lecture du fichier Audio, on enregistre ses valeur dans le vecteur morseSignal en valeur absolue
		fread(meta, 1, sizeof(header), infile);
		while (!feof(infile))
		{
			nb = fread(buff16,1,BUFSIZE,infile);
			
			if (buff16[0] > 0){
				morseSignal.push_back((buff16[0]));
			}
			else{
				morseSignal.push_back(-buff16[0]);
			}
		}
		/// On initialise value pour savoir si le signal commence par un espace ou non
		if(morseSignal[0] == 0){
			isValue = false;
		}
		/// On calcule le temps de chaque element du signal puis on le convertit en morse
		for(int i = 0 ; i<morseSignal.size() ; i++){
			if(((morseSignal[i] > 0) && isValue) || (morseSignal[i] ==0 && !isValue)){
				currentCount +=1;
			}
			else{
				if(isValue && (abs(30 - currentCount) < 5)){
					sentence+=".";
				}
				else if(isValue && (abs(60 - currentCount) < 5)){
					sentence+="-";
				}
				else if(!isValue && (abs(30 - currentCount) < 5)){
					sentence+=" ";
				}
                else if(!isValue && currentCount > 40){
                    sentence+=" / ";
                }
				currentCount = 0;
				isValue = !isValue;
			}
		}

        /// On convertit le message en morse en un message francais (ou autre)
        std::string temp;
        std::cout<< "le message est : \n";
        
        for (int i=0 ; i < sentence.length() ; i++ )  {
            if(sentence[i] == ' '){
                decoder_car(temp);
                temp ="";
                continue;
            }
            temp+=sentence[i];
        }
        decoder_car(temp);
	}
    else{
        std::string msg = "(" + filePath +
                                "): ce chemin ne correspond à aucun audio (format wav)";
        throw std::invalid_argument(msg);
    }
    std::cout<<std::endl;
}

void encoder_msg(){
    ///  On récupere le message à coder ainsi que le chemin de l'audio à enregistrer
    std::string sentence;
    std::string filePath;
    std::cout<<"\nMessage à encoder :\n";
    getline(std::cin >> std::ws, sentence);
    std::cout<<"\nnom du fichier audio à enregistrer (avec .wav):\n";
    getline(std::cin >> std::ws, filePath);
    std::cout<< "le message en morse est : \n";

    /// definitions des constantes pour la création du fichier .wav
    const std::string chunk_id = "RIFF";
    const std::string chunk_size = "----";
    const std::string format = "WAVE";
    const std::string subchunk1_id = "fmt ";
    const int subchunk1_size = 16;
    const int audio_format = 1;
    const int num_channels = 1;
    const int sample_rate = 44100;
    const int byte_rate = sample_rate * num_channels * (subchunk1_size/2) ;
    const int block_align = num_channels * (subchunk1_size / 8);
    const int bits_per_sample = 16;
    const std::string subchunk2_id = "data";
    const std::string subchunk2_size = "----";

    /// definitions des conventions pour le morse audio
    const int dot_duration = 8000; //longueur d'un ., demie longueur d'un -
    const int intra_duration = 2000; // pause entre chaque . ou -, qui est demultiplié entre chaque caractère (*3), et encore plus entre chaque mot (*5)
    int amplitude = 18000; // amplitude du signal
    const double frequency = 440; // frequence en hz

    /// Creation de l'audio
    std::ofstream wav;
    wav.open(filePath.c_str(),std::ios::binary);
    if (wav.is_open())
    {
        wav << chunk_id;
        wav << chunk_size;
        wav << format;
        wav << subchunk1_id;
        write_as_bytes(wav, subchunk1_size,4);
        write_as_bytes(wav, audio_format,2);
        write_as_bytes(wav, num_channels, 2);
        write_as_bytes(wav, sample_rate,4);
        write_as_bytes(wav, byte_rate, 4);
        write_as_bytes(wav, block_align,2);
        write_as_bytes(wav, bits_per_sample,2);

        wav << subchunk2_id;
        wav << subchunk2_size;

        int start_audio = wav.tellp();
        for (char c : sentence)
        {
            if (morseCodeMap.count(c) > 0){
                //convertion du caractère en morse
                std::string morse = morseCodeMap[c];
                std::cout<<morse<<" ";
                //chaque composante du caractère morse et transformée en audio individuellement
                for(char c : morse){
                    int duration;
                    int amp;
                    if(c == '.'){
                        amp = amplitude;
                        duration = dot_duration;
                    }
                    if(c == '-'){
                        amp = amplitude;
                        duration = dot_duration * 2;
                    }
                    if(c == ' '){
                        amp = 0;
                        duration = intra_duration;
                    }
                    if(c == '/'){
                        amp = 0;
                        duration = intra_duration *5;
                    }
                    for( int i=0; i< duration; i++){
                        double signal = amp * sin((2*3.14*i*frequency)/sample_rate);
                        write_as_bytes(wav,signal,2);
                    }
                    for( int i=0; i< intra_duration; i++){
                    write_as_bytes(wav,0,2);
                }
                }
                for( int i=0; i< intra_duration*3; i++){
                    write_as_bytes(wav,0,2);
                }
            }
            else{
                std::string  car;
                car.push_back(c);
                std::string msg = "(" + car +
                                "): ce caractère ne peut pas être codé en morse";
                throw std::invalid_argument(msg);
            }
        }

        int end_audio = wav.tellp();
        wav.seekp(start_audio - 4);
        write_as_bytes(wav, end_audio - start_audio, 4);
        wav.seekp(4, std::ios::beg);
        write_as_bytes(wav,end_audio -8,4);
        wav.close();
    }
    else{
        std::string msg = "(" + filePath +
                                "): ce chemin n'est pas au bon format ou inaccessible(.wav)";
        throw std::invalid_argument(msg);
    }
    std::cout<<std::endl;
    std::cout<<"\nLe message à été encodé sous forme d'audio dans le fichier "<<filePath<<std::endl;
}

int main(){
    bool quit = false; //arret du programme

    /// On demande l'action à effectuer tant que le programme n'est pas arrété
    while(quit == false){
        std::cout << "\nQuelle action effectuer ? : " <<std::endl;
        std::cout << "   - 1 : encoder un message " <<std::endl;
        std::cout << "   - 2 : decoder un message " <<std::endl;
        std::cout << "   - 3 : quitter le programme " <<std::endl;
        std::string actionstring;
        std::cout<<"action(1/2/3) : ";

        std::cin >> actionstring;
        if (!(actionstring == "1" || actionstring == "2" || actionstring == "3")){
            std::string msg = "(" + actionstring +
                              "): Cette action n'est pas répertoriée";
            throw std::invalid_argument(msg);
        }

        int action = std::stoi( actionstring );

        if(action == 1)
        {
            encoder_msg();
        }
        else if(action == 2)
        {
            decoder_msg();
        }
        else if(action == 3)
        {
            quit = true;
        }
    }
    return 0;
}