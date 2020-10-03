#include "Tileset.hpp"
#include <iostream>
#include <fstream>


void Tileset::load_from_file(){

	//std::cout<<"tileset::load_from_file"<<std::endl;
	std::ifstream tileset_stream(file_name+".tileset");

	int max=100;
	char*raw;
	raw=(char*)malloc(max);

	if(tileset_stream.is_open()){
		tileset_stream.get(raw,max,'x');
		tile_width=atoi(raw);
		tileset_stream.get();

		tileset_stream.get(raw,max,':');
		tile_height=atoi(raw);
		tileset_stream.get();

		if(tileset_stream.peek()=='b'){
			tileset_stream.get();
			tileset_stream.get(raw,max,'x');
			buffer_x=atoi(raw);
			tileset_stream.get();

			tileset_stream.get(raw,max,'\n');
			buffer_y=atoi(raw);
		}
		tileset_stream.get();

		tileset_stream.get(raw,max,'x');
		size_x=atoi(raw);
		tileset_stream.get();

		tileset_stream.get(raw,max,'\n');
		size_y=atoi(raw);
		tileset_stream.get();


		while(!tileset_stream.eof()){
			tileset_stream.get(raw,max,'\n');
			tileset.push_back(raw);
			tileset_stream.get();
		}


	}else{
		std::cout<<"ERROR opening file: "<<file_name<<std::endl;
	}
	//std::cout<<size_x<<"X"<<size_y<<":b"<<buffer_x<<"x"<<buffer_y<<std::endl;
	//for(int i=0;i<(int)tileset.size();i++){
	//	std::cout<<tileset.at(i)<<std::endl;
	//}
	//std::cout<<std::endl;

	//std::cout<<"~tileset::load_from_file"<<std::endl;
}


int Tileset::type_s_to_int(std::string s_p){
	for(int i=0;i<(int)tileset.size();i++){
		if(tileset.at(i).substr(0,tileset.at(i).find(':'))==s_p){
			return i;
		}
	}
	std::cout<<"ERROR: tile type "<<s_p<<" not found in set "<<name<<std::endl;
	return -1;
}