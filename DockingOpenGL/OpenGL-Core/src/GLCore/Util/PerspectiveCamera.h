#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace GLCore::Utils {

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera();

		void Update(glm::vec3 camPos, glm::vec3 camTar, float fov_y, float aspectRatio);

		void Recalculate();

		void SetProjection(float fvo_y,float aspect_ratio,float z_near,float z_far);
		void SetView(glm::vec3 camera_position,glm::vec3 look_at,glm::vec3 camera_up);
		void SetAspectRatio(float ratio);
		void SetFOVY(float fovy);
		void SetPosition(glm::vec3 posiiton);
		void SetPositionOffset(glm::vec3 position_offset);
		void SetPositionOffsetSpherical(glm::vec2 position_offset);
		void SetStare(glm::vec3 stare);
		
		const glm::mat4& GetProjectionMatrix() const { return mat_projection_; }
		const glm::mat4& GetViewMatrix() const { return mat_view_; }
		const glm::mat4& GetViewProjectionMatrix() const { return mat_view_projection_; }
		const float GetFar() { return z_far_; }
		const float Getnear() { return z_near_; }

	private:
		// matrices need calculated
		glm::mat4 mat_projection_;
		glm::mat4 mat_view_;
		glm::mat4 mat_view_projection_;

		// camera status
		glm::vec3 position_;
		glm::vec3 stare_;
		glm::vec3 front_;
		glm::vec3 up_;
		glm::vec3 right_;
		glm::vec3 world_up_;

		float yaw_;
		float pitch_;
		float roll_;
		
		float fov_y_;
		float aspect_ratio_;
		float z_near_=0.01;
		float z_far_=100.f;
	};


}




