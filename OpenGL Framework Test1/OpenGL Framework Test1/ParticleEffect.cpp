#include "ParticleEffect.h"
#include "MathFunc.h"

#define BUFFER_OFFSET(i) ((char *) 0 + (i))


ParticleEffect::ParticleEffect()
{
}

ParticleEffect::~ParticleEffect()
{
	if (VAO != GL_NONE)
	{
		glDeleteVertexArrays(1, &VAO);
	}

	if (VBO_Position != GL_NONE)
	{
		glDeleteBuffers(1, &VBO_Position);
	}
	
	if (VBO_Size != GL_NONE)
	{
		glDeleteBuffers(1, &VBO_Size);
	}
	
	if (VBO_Alpha != GL_NONE)
	{
		glDeleteBuffers(1, &VBO_Alpha);
	}

	if (m_particles.Positions != nullptr)
	{
		delete[] m_particles.Positions;
		delete[] m_particles.Velocities;
		delete[] m_particles.Alpha;
		delete[] m_particles.Ages;
		delete[] m_particles.Lifetimes;
		delete[] m_particles.Size;
	}
}

bool ParticleEffect::Init(const std::string &textureFile, unsigned int maxParticles, unsigned int rate)
{
	if (!m_texture.Load(textureFile)) {
		return false;
	}

	m_maxParticles = maxParticles;
	m_rate = rate;

	m_particles.Positions = new glm::vec3[m_maxParticles];
	m_particles.Velocities = new glm::vec3[m_maxParticles];
	m_particles.Alpha = new float[m_maxParticles];
	m_particles.Ages = new float[m_maxParticles];
	m_particles.Lifetimes = new float[m_maxParticles];
	m_particles.Size = new float[m_maxParticles];

	//Setup OpenGL memory
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO_Position);
	glGenBuffers(1, &VBO_Size);
	glGenBuffers(1, &VBO_Alpha);

	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);		//Vertex (Position)
	glEnableVertexAttribArray(1);		//Sizes
	glEnableVertexAttribArray(2);		//Alpha
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_maxParticles, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Size);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_maxParticles, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer((GLuint)1, 1, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Alpha);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_maxParticles, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer((GLuint)2, 1, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
	glBindVertexArray(GL_NONE);

	return true;
}

void ParticleEffect::Update(float elapsed)
{
	int NumToSpawn = m_rate;

	/// Create new particles ///
	while (
		//We have not reached the particle cap and...
		m_numCurrentParticles < m_maxParticles &&
		//We have more particles to generate this frame...
		NumToSpawn > 0)
	{
		m_particles.Alpha[m_numCurrentParticles]		= LerpAlpha.x;
		m_particles.Ages[m_numCurrentParticles]		= 0.0f;
		m_particles.Lifetimes[m_numCurrentParticles]	= RandomRangef(RangeLifetime.x, RangeLifetime.y);
		m_particles.Size[m_numCurrentParticles]		= LerpSize.x;
		m_particles.Positions[m_numCurrentParticles]  = glm::vec3(RandomRangef(RangeX.x, RangeX.y), RandomRangef(RangeY.x, RangeY.y), RandomRangef(RangeZ.x, RangeZ.y));

		//send the particle in a random direction, with a velocity between our range
		m_particles.Velocities[m_numCurrentParticles] = glm::vec3(RandomRangef(-1.0f, 1.0f), RandomRangef(-1.0f, 1.0f), RandomRangef(-1.0f, 1.0f));
		m_particles.Velocities[m_numCurrentParticles] = glm::normalize(m_particles.Velocities[m_numCurrentParticles]);
		m_particles.Velocities[m_numCurrentParticles] *= RandomRangef(RangeVelocity.x, RangeVelocity.y);

		//counters...
		m_numCurrentParticles++;
		NumToSpawn--;
	}

	/// Update existing particles ///
	for (unsigned i = 0; i < m_numCurrentParticles; i++)
	{
		m_particles.Ages[i] += elapsed;

		if (m_particles.Ages[i] > m_particles.Lifetimes[i])
		{
			//remove the particle by replacing it with the one at the top of the stack
			m_particles.Alpha[i]		= m_particles.Alpha[m_numCurrentParticles - 1];
			m_particles.Ages[i]		= m_particles.Ages[m_numCurrentParticles - 1];
			m_particles.Lifetimes[i] = m_particles.Lifetimes[m_numCurrentParticles - 1];
			m_particles.Positions[i] = m_particles.Positions[m_numCurrentParticles - 1];
			m_particles.Size[i]		= m_particles.Size[m_numCurrentParticles - 1];
			m_particles.Velocities[i] = m_particles.Velocities[m_numCurrentParticles - 1];

			m_numCurrentParticles--;
			continue;
		}

		m_particles.Positions[i] += m_particles.Velocities[i] * elapsed;

		float interp = m_particles.Ages[i] / m_particles.Lifetimes[i];
		
		m_particles.Alpha[i] = Lerp(LerpAlpha.x, LerpAlpha.y, interp);
		m_particles.Size[i]	= Lerp(LerpSize.x, LerpSize.y, interp);
	}

	//update opengl on the changes

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Position);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * m_numCurrentParticles, &m_particles.Positions[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Size);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * m_numCurrentParticles, &m_particles.Size[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Alpha);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * m_numCurrentParticles, &m_particles.Alpha[0]);
}

void ParticleEffect::Render()
{
	if (m_numCurrentParticles == 0)
	{
		return;
	}

	m_texture.Bind(0);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, m_numCurrentParticles);
	glBindVertexArray(GL_NONE);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	m_texture.Unbind(0);
}

void ParticleEffect::setRate(float rate)
{
	m_rate = rate;
}

float ParticleEffect::getRate()
{
	return m_rate;
}

unsigned int ParticleEffect::getCurrent()
{
	return m_numCurrentParticles;
}

unsigned int ParticleEffect::getMax()
{
	return m_maxParticles;
}
