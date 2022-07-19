#include "glpch.h"
#include "PerspectiveCamera.h"



GLCore::Utils::PerspectiveCamera::PerspectiveCamera()
{
}



void GLCore::Utils::PerspectiveCamera::Recalculate()
{
}

void GLCore::Utils::PerspectiveCamera::SetAspectRatio(float ratio)
{
	aspect_ratio_ = ratio;
}

void GLCore::Utils::PerspectiveCamera::SetFOVY(float fovy)
{
	fov_y_ = fovy;
}

void GLCore::Utils::PerspectiveCamera::SetPosition(glm::vec3 posiiton)
{
	position_ = posiiton;
}

void GLCore::Utils::PerspectiveCamera::SetPositionOffset(glm::vec3 position_offset)
{
	position_ += position_offset;
}

void GLCore::Utils::PerspectiveCamera::SetPositionOffsetSpherical(glm::vec2 position_offset)
{
	



}

void GLCore::Utils::PerspectiveCamera::SetStare(glm::vec3 stare)
{
	stare_ = stare;
}

void GLCore::Utils::PerspectiveCamera::Update(glm::vec3 camPos, glm::vec3 camTar, float fov_y, float aspectRatio)
{

	position_ = camPos;
	front_ = glm::normalize(camTar-camPos);
	fov_y_ = fov_y;
	aspect_ratio_ = aspectRatio;

	// Calculate The Up Vector
	// Ref: https://learnopengl.com/Getting-started/Camera
	world_up_ = glm::vec3(0, 0, 1);
	right_ = glm::normalize(glm::cross(front_, world_up_));
	up_ = glm::normalize(glm::cross(right_, front_));
	//up_ = glm::vec3(0, 0, 1);

	// Calculate The View & Projection Matrix
	mat_view_ = glm::lookAt(position_, camTar, up_);

	mat_projection_ = glm::perspective(fov_y_, aspect_ratio_, z_near_, z_far_);

	mat_view_projection_ = mat_projection_ * mat_view_;

}

