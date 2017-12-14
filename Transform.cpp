#include "Transform.h"
#include <vector>
#include <iostream>

void Transform::addChild(Node* childNode){
	nodeList.push_back(childNode);
}

void Transform::removeChild(Node* childNode){
	nodeList.pop_back();
}

void Transform::draw(glm::mat4 C) {
	for (int i = 0; i < nodeList.size(); i++)
	{
		auto node = nodeList[i];
		node->draw(C*M);
	}
}

void Transform::update() {

}

glm::mat4 Transform::getMatrix() {
	return M;
}

void Transform::setMatrix(glm::mat4 mat) {
	M = mat;
}

