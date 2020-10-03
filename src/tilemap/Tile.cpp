#include "Tile.hpp"
#include "Tileset.hpp"
#include <iostream>

void Tile::load(int x_p, int y_p, Tileset tileset_p, std::string load_p){

	//std::cout<<"tile::load"<<std::endl;
	map_x=x_p;
	map_y=y_p;

	//std::cout<<x_p<<","<<y_p<<":"<<load_p<<std::endl;


	hitbox.create(map_x*tileset_p.get_tile_width(),map_y*tileset_p.get_tile_height(),tileset_p.get_tile_width(),tileset_p.get_tile_height());
	tile_type=-1;
	char c='?';
	for(int i=0;i<(int)load_p.size();i++){

		if(tile_type==-1){
			if (load_p.at(i)>='0' &&load_p.at(i)<='9'){
				for(int j=i;j<(int)load_p.size();j++){
					if(load_p.at(j)<'0'|| load_p.at(j)>'9'){
						tile_type=std::stoi(load_p.substr(i,j-i));
						type_image_int=tile_type;
						i=j-1;
						break;
					}
					if(j+1==load_p.size()){
						tile_type=std::stoi(load_p.substr(i,(j+1)-i));
						type_image_int=tile_type;
						i=j;
						break;
					}
				}
			}
		}else{
			c=load_p.at(i);
			if(c=='r'){
				if(i+1>=load_p.size()){
					std::cout<<"ERROR: bad rotation info at "<<map_x<<","<<map_y<<std::endl;
				}
				rotation_int=load_p.at(i+1)-48;
				if(rotation_int<0 || rotation_int>3){
					std::cout<<"ERROR: bad rotation int: "<<rotation_int<<" at "<<map_x<<","<<map_y<<std::endl;
					rotation_int=0;
				}
				i++;
			}else if(c=='d'){

			}
		}	

	}

	if(tile_type>=0 && tile_type<tileset_p.get_set_size()){
		std::string info_from_set=tileset_p.at(tile_type);
		int current_index=info_from_set.find(':');
		type_s=info_from_set.substr(0,current_index);
		while(current_index<info_from_set.size()){
			if(info_from_set.at(current_index)=='S'){
				solid=true;
			}

			if(info_from_set.at(current_index)=='G'){
				current_index++;
				if(info_from_set.at(current_index)=='-'){
					visible=false;
				}else{
					for(int j=current_index;j<(int)info_from_set.size();j++){
						if(info_from_set.at(j)<'0'|| info_from_set.at(j)>'9'){
							type_image_int=std::stoi(info_from_set.substr(current_index,j-current_index));
							current_index=j;
							break;
						}
						if(j+1==info_from_set.size()){
							type_image_int=std::stoi(info_from_set.substr(current_index,j+1-current_index));
							current_index=j;
							break;
						}
					}
				}
			}
			current_index++;
		}
	}else{
		std::cout<<"ERROR: invalid tile_type "<<tile_type<<" at tile: "<<map_x<<","<<map_y<<std::endl;
	}
	//std::cout<<"tile:"<<map_x<<","<<map_y<<":"<<type_s<<":S"<<solid<<"V"<<visible<<std::endl;
	//std::cout<<"~tile::load"<<std::endl;

}