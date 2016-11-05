#ifndef OBJECT_H
#define OBJECT_H




/*
what we need to store:
-Its own model matrix
--vertices (the model)
--position
-- angle: is this local or world? (probably local)
--scale
-what enum type (GL_STATIC_DRAW, GL_DYNAMIC_DRAW...) This is an optimzation I will worry
about once I get it up and running. For now they are all static.

what we need it to do:
- spawn itself:
-- allocate own memory
-- deal with buffers*
- despawn itself:
--free(self)
--tell the buffer it has been despawned*

*thoughts on the handling the buffers:
- If two objects share the same model, why should the same model be loaded twice?
they would just have different model matrices. UPDATED: what you would do is draw the same
VAO twice but change the uniform between drawing.
-

- Most of this is to be implemented in the future as it would confuse me before I get it up
and running.




things that would be interesting in the future:
-momentum
-angular momentum
-
*/
#include <GL/glew.h>




class object{
    public:
        /** Default constructor */
        object();
        /** Default destructor */
        virtual ~object();
        /** Access objectCount
         * \return The current value of objectCount
         */
        static int GetobjectCount() { return objectCount; }
        /** Set objectCount
         * \param val New value to set
         */
        void SetobjectCount(static int val) { objectCount = val; }
        /** Access worldPosition
         * \return The current value of worldPosition
         */
        position GetworldPosition() { return worldPosition; }
        /** Set worldPosition
         * \param val New value to set
         */
        void SetworldPosition(position val) { worldPosition = val; }
        /** Access rotationAngle
         * \return The current value of rotationAngle
         */
        angle GetrotationAngle() { return rotationAngle; }
        /** Set rotationAngle
         * \param val New value to set
         */
        void SetrotationAngle(angle val) { rotationAngle = val; }

        void spawn(); // it gets loaded in the constructor and rendering begins here
        // before spawning, calls to draw will do nothing.
        // remember: what you do when rendering is:
        // for each object(change the uniform model matrix -> render next obj)


    protected:
    private:
        static int objectCount; //!< Member variable "objectCount"
        position worldPosition; //!< Member variable "worldPosition"
        angle rotationAngle; //!< Member variable "rotationAngle"
        object model; // the data from the file
        GLuint vao;
        GLuint ebo;
        GLuint vbo;
        GLuint uniModel;
        bool spawned;
};

#endif // OBJECT_H

/*
[14:35] <anon_lastname> Hello, anybody know where I can get information about how to handle rendering multiple shapes at once
[14:36] <afl_ext> anon_lastname but you can render one shape now right?
[14:37] <anon_lastname> aft_ext Yes I just don't get how to go about rendering n at a time
[14:37] <anon_lastname> like how to manage the buffers and stuff
[14:37] <afl_ext> do you use VAOs for rendering your shape?
[14:38] <anon_lastname> yes
[14:38] <afl_ext> then why you dont just create another set of array+element buffers
[14:38] <afl_ext> create another vao
[14:38] <afl_ext> and tnder just after the first shape?
[14:38] <afl_ext> possibly you may want to enable depth test
[14:39] <anon_lastname> SO you just create a new VAO for each shape?
[14:39] <afl_ext> yes
[14:39] <afl_ext> of course only once
[14:39] <afl_ext> and then you just bind it and draw
[14:39] <afl_ext> every frame
[14:41] <anon_lastname> Ok can you create a new uniform for just that shape? for example if I want a shape to have a different model matrix\
[14:42] <afl_ext> you can have uniform in shader for example names modelmatrix
[14:42] <afl_ext> anon_lastname^
[14:42] <afl_ext> anon_lastname and then you set its value, render first shape, then change to other value and render second
[14:43] <anon_lastname> afl_ext thank you I will try to implement that


*/








