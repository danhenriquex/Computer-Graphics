#include"objloader.h"
#include<vector>
#include <iostream>
// Include AssImp
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include<string>

#include <GL/glew.h>

class object{

private:
	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	std::string filename;
public:
	void drawObj();
	void import(char *path);
	void tras(glm::mat4 transfor);
    void tras_normal(glm::mat4 transfor);



private:
    GLuint tex;


};
