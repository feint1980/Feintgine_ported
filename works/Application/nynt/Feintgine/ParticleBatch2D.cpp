#include "ParticleBatch2D.h"

namespace Feintgine
{
	ParticleBatch2D::ParticleBatch2D() {
		// Empty
	}


	ParticleBatch2D::~ParticleBatch2D() {
		delete[] m_particles;
	}

	void ParticleBatch2D::init(int maxParticles,
		float decayRate,
		const F_Sprite & sprite,
		std::function<void(Particle2D&,float)> updateFunc /* = defaultParticleUpdate */) {
		m_maxParticles = maxParticles;
		m_particles = new Particle2D[m_maxParticles];
		m_decayRate = decayRate;
		m_sprite = sprite;
		m_updateFunc = updateFunc;
	}

	void ParticleBatch2D::init(int maxParticles,
		float decayRate,
		const F_AnimatedObject & animatedObejct,
		std::function<void(Particle2D&,float)> updateFunc /* = defaultParticleUpdate */) {
		m_maxParticles = maxParticles;
		m_particles = new Particle2D[maxParticles];
		m_decayRate = decayRate;
		m_animatedObject = animatedObejct;
		bool m_isAnimated = true;
		m_updateFunc = updateFunc;
		//m_animatedObject.playAnimation("idle");
	}

	void ParticleBatch2D::update(float deltaTime) {
		for (int i = 0; i < m_maxParticles; i++) {
			// Check if it is active
			if (m_particles[i].life > 0.0f) {
				// Update using function pointer
				m_updateFunc(m_particles[i],deltaTime);
				m_particles[i].life -= m_decayRate * deltaTime;
			}
		}
	}

	void ParticleBatch2D::draw(SpriteBatch* spriteBatch) {
		//glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
		if (!m_isAnimated)
		{
			glm::vec4 uvRect = m_sprite.getUV();
			for (int i = 0; i < m_maxParticles; i++) {
				// Check if it is active
				auto& p = m_particles[i];
				if (p.life > 0.0f) {
					glm::vec4 destRect(p.position.x, p.position.y, p.scale * m_sprite.getDim().x, p.scale * m_sprite.getDim().y);
					spriteBatch->draw(destRect, uvRect, m_sprite.getTexture().id, m_depth, p.color,p.angle);
				}
			}
		}
		else
		{
			for (int i = 0; i < m_maxParticles; i++) {
				// Check if it is active
				auto& p = m_particles[i];
				if (p.life > 0.0f) {
					m_animatedObject.setPos(p.position);
					m_animatedObject.setScale(glm::vec2(p.scale));
					m_animatedObject.draw(*spriteBatch);
				}
			}
			
		}
	}

	void ParticleBatch2D::addParticle(const glm::vec2& position,
		const glm::vec2& velocity,
		const Color& color,
		float scale) {
		int particleIndex = findFreeParticle();

		auto& p = m_particles[particleIndex];

		p.life = 1.0f;
		p.position = position;
		p.velocity = velocity;
		p.color = color;
		p.scale = scale;
	}

	int ParticleBatch2D::findFreeParticle() {

		for (int i = m_lastFreeParticle; i < m_maxParticles; i++) {
			if (m_particles[i].life <= 0.0f) {
				m_lastFreeParticle = i;
				return i;
			}
		}

		for (int i = 0; i < m_lastFreeParticle; i++) {
			if (m_particles[i].life <= 0.0f) {
				m_lastFreeParticle = i;
				return i;
			}
		}

		// No particles are free, overwrite first particle
		return 0;
	}
}


