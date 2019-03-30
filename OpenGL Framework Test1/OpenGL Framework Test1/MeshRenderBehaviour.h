#ifndef __MESHRENDERBEHAVIOUR_H__
#define __MESHRENDERBEHAVIOUR_H__

#include "Behaviour.h"
#include "Model.h"
#include "IModel.h"
#include "AnimatedModel.h"

class MeshRenderBehaviour : public Behaviour {
public:
	MeshRenderBehaviour(Model* _model, Shader* _shader, const bool& _transparent = false);
	MeshRenderBehaviour(IModel* _model, Shader* _shader, const bool& _transparent = false);
	MeshRenderBehaviour(AnimatedModel* _model, Shader* _shader, const bool& _transparent = false);
	~MeshRenderBehaviour();

	void start() override;
	void update() override;
	void render() override;
	void renderTransparent() override;
	void renderGUI() override;

	void swapAnim(AnimatedModel *_new);

private:
	Model* m_model;
	IModel* m_iModel;
	AnimatedModel *m_aModel;

	Shader* m_shader;
	bool m_transparent : 1;
	bool m_IMDL : 1;
	bool m_animated : 1;
};
#endif
