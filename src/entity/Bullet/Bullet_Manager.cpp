#include "Bullet_Manager.hpp"
#include "../../image/Imagehandler.hpp"

Bullet_Manager::Bullet_Manager():tree(Point(10,10),Point(1360,760),0){

}

void Bullet_Manager::load_animations(Imagehandler& imagehandler){
	linear_bullet.load_animations(imagehandler);
	sine_bullet.load_animations(imagehandler);
	homing_bullet.load_animations(imagehandler);
	linear_bullet.scale_animations(Point(0.2f,0.2f));
	sine_bullet.scale_animations(Point(0.2f,0.2f));
	homing_bullet.scale_animations(Point(0.2f,0.2f));
}

void Bullet_Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	
	for(int i=0;i<(int)live_bullets.size();i++){		
		target.draw(*live_bullets.at(i), states);
	}

	target.draw(tree,states);
	//for(int i=0;i<(int)tree.rectangles.size();i++){
	//	target.draw(tree.rectangles.at(i),states);
		//std::cout<<tree.rectangles.at(i).getPosition().x<<std::endl;
	 //}
} 



Bullet_Vector Bullet_Manager::bullets_colliding_with_hitbox(Circular_Hitbox hitbox_p){
	Bullet_Vector colliding_bullets=Bullet_Vector();
	/*for(int i=0;i<(int)live_bullets.size();i++){
		if(live_bullets.at(i)->get_hitbox().is_colliding(hitbox_p)){
			colliding_bullets.push_back(live_bullets.at(i));
		}
	}*/
	//colliding_bullets=tree.get_collidable_bullets(hitbox_p.get_center());
	colliding_bullets=tree.get_collidable_bullets_bound(hitbox_p.get_center()-Point(hitbox_p.get_radius(),hitbox_p.get_radius()),
		hitbox_p.get_center()+Point(hitbox_p.get_radius(),hitbox_p.get_radius()));
	return colliding_bullets;
}

void Bullet_Manager::capture_bullets(std::vector<Point> line_p){
}

void Bullet_Manager::add_bullets(std::vector<Bullet_Blueprint> blueprints_p){
	for(int i=0;i<(int)blueprints_p.size();i++){
		if(blueprints_p.at(i).type==LINEAR){
			//live_bullets.push_back(make_unique<Linear_Bullet>(linear_bullet.create_copy(blueprints_p.at(i))));
			tree.insert(make_unique<Linear_Bullet>(linear_bullet.create_copy(blueprints_p.at(i))));

			//std::cout<<"base depth: "<<tree.get_depth()<<std::endl;
		}else if(blueprints_p.at(i).type==SINE){
			//live_bullets.push_back(make_unique<Sine_Bullet>(sine_bullet.create_copy(blueprints_p.at(i))));
			tree.insert(make_unique<Sine_Bullet>(sine_bullet.create_copy(blueprints_p.at(i))));
			//std::cout<<"base depth: "<<tree.get_depth()<<std::endl;
		}else if(blueprints_p.at(i).type==HOMING){
			//live_bullets.push_back(make_unique<Homing_Bullet>(homing_bullet.create_copy(blueprints_p.at(i))));
			tree.insert(make_unique<Homing_Bullet>(homing_bullet.create_copy(blueprints_p.at(i))));
			//std::cout<<"base depth: "<<tree.get_depth()<<std::endl;
		}
		//std::cout<<endl;
	}
}

void Bullet_Manager::update(){
	/*for(int j=0;j<live_bullets.size();j++){
		auto it= live_bullets.at(j);
		if(it->is_exploding()==false){
			Bullet_Vector collisions=tree.get_collidable_bullets(it->get_center());
			//Bullet_Vector collisions=live_bullets;
			for (int i=0;i<collisions.size();i++){
				if(it->is_colliding(*collisions.at(i))&&collisions.at(i)!=it){
					//it->set_exploding(true);
					//std::cout<<"erasing bullet at "<<center.get_x()<<", "<<center.get_y()<<std::endl;
				}
			}
		}
			
	}*/
	live_bullets=tree.get_all_bullets();
	tree.update();
}

void Bullet_Manager::update_player_position(Point pos_p){
	for(int i=0;i<(int)live_bullets.size();i++){
	}
}