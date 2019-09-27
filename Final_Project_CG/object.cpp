#include "object.h"
#include "SDLImage.h"

void object::tras(glm::mat4 transfor){


  for(int i = 0 ; i < this->indexed_vertices.size();i++ ){

    glm::vec4 aux = glm::vec4(this->indexed_vertices[i],1.0);
    aux = glm::vec4( transfor * aux );
    this->indexed_vertices[i]= glm::vec3(aux);

    aux = glm::vec4(this->indexed_normals[i],1.0);
    aux = glm::vec4(transfor * aux);
    this->indexed_normals[i]= normalize(glm::vec3(aux));
 }


};


void object::drawObj(){

    glewInit();

	GLuint VertexVBOID;
    glGenBuffers(1, &VertexVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3)*indexed_vertices.size())+(sizeof(glm::vec3)*indexed_normals.size())+(sizeof(glm::vec2)*indexed_uvs.size()),0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, (sizeof(glm::vec3)*indexed_vertices.size()), &indexed_vertices[0].x);                             // copy vertices starting from 0 offest

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * indexed_vertices.size(), sizeof(glm::vec3)*indexed_normals.size(), &indexed_normals[0].x);                // copy normals after vertices
//
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*indexed_vertices.size() + sizeof(glm::vec3)*indexed_normals.size(), sizeof(glm::vec2) * indexed_uvs.size() , &indexed_uvs[0].x);




	GLuint IndexVBOID;
    glGenBuffers(1, &IndexVBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*indices.size(), &this->indices[0], GL_STATIC_DRAW);



    SDLImage image(filename);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
// Define this somewhere in your header file
    #define BUFFER_OFFSET(i) ((char*)(i))



    glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(glm::vec3),0);    // The starting point of the VBO, for the vertices

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(glm::vec3),(char*)(sizeof(glm::vec3)*indexed_vertices.size()));      // The starting point of normals, 12 bytes away
//
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(glm::vec2), (char*)(sizeof(glm::vec3)*indexed_vertices.size() + sizeof(glm::vec3)*indexed_normals.size()));

    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBOID);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

    glDeleteBuffers(1, &IndexVBOID);
    glDeleteBuffers(1, &VertexVBOID);
    glDeleteTextures(1, &tex);


}

void object::import(char *path){

//    std::string filename;
	bool res = loadAssImp(path, filename, this->indices, this->indexed_vertices, this->indexed_uvs, this->indexed_normals);
//    SDLImage image("Yoda_D.png");

//    glGenTextures(1, &tex);
//    glBindTexture(GL_TEXTURE_2D, tex);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
}
