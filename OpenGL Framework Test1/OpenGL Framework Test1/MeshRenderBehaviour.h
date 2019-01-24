#ifndef __MESHRENDERBEHAVIOUR_H__
#define __MESHRENDERBEHAVIOUR_H__

#include "Behaviour.h"
#include "Model.h"
#include "IModel.h"

class MeshRenderBehaviour : public Behaviour {
public:
	MeshRenderBehaviour(Model* _model, Shader* _shader, const bool& _transparent = false);
	MeshRenderBehaviour(IModel* _model, Shader* _shader, const bool& _transparent=false);
	~MeshRenderBehaviour();

	void start() override;
	void update() override;
	void render() override;
	void renderTransparent() override;
	void renderGUI() override;

private:
	Model* m_model;
	IModel* m_iModel;
	Shader* m_shader;
	bool m_transparent;
	bool m_IMDL;
};
#endif
