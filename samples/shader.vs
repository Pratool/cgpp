#version 330

out gl_PerVertex { vec4 gl_Position; };

void main()
{
    gl_Position = vec4(0.5 * Position.x, 0.5 * Position.y, Position.z, 1.0);
}
