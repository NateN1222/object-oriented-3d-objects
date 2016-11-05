#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED


#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/gl.h>

#include "object.hpp"

class camera{
    public:
        /** Default constructor */
        camera(glm::vec3 Pos, glm::vec3 Ang);
        /** Default destructor */
        virtual ~camera();
        /** Access objectCount
         * \return The current value of objectCount
         */
        glm::vec3 GetworldPosition() { return worldPosition; }
        /** Set worldPosition
         * \param val New value to set
         */
        void SetworldPosition(glm::vec3 val) { worldPosition = val; }
        /** Access rotationAngle
         * \return The current value of rotationAngle
         */
        //glm::vec3 GetrotationAngle() { return rotationAngle; }
        /** Set rotationAngle
         * \param val New value to set
         */
        //void SetrotationAngle(angle val) { rotationAngle = val; }

        void spawn(); // it gets loaded in the constructor and rendering begins here
        // before spawning, calls to draw will do nothing.
        // remember: what you do when rendering is:
        // for each object(change the uniform model matrix -> render next obj)
        void draw();

        void debug_set(float offset) { debug_offset = offset; }

    protected:
    private:
        glm::vec3 worldPosition; //!< Member variable "worldPosition"
        glm::vec3 rotationAngle; //!< Member variable "rotationAngle"
        bool spawned;
        GLuint uniView;
        float debug_offset;
};


#endif // CAMERA_HPP_INCLUDED
