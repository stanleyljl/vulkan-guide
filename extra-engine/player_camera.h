// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <glm/glm.hpp>
#include <vk_types.h>


struct PlayerCamera {
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 inputAxis;

	float pitch{ 0 }; //up-down rotation
	float yaw{ 0 }; //left-right rotation

	bool bSprint = false;
	bool bLocked;

	void update_camera(float deltaSeconds);


	glm::mat4 get_view_matrix();
	glm::mat4 get_projection_matrix(float width, float height, bool bReverse = true);
	glm::mat4 get_rotation_matrix();
};
