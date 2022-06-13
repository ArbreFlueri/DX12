#pragma once
#include "Component.h"

class Transform;
class MeshRenderer;
class MonoBehaviour;

class GameObject : public enable_shared_from_this<GameObject>
{
public :
	GameObject();
	virtual ~GameObject();

	void Init();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();

	shared_ptr<Transform> GetTransform();

	void AddComponent(shared_ptr<Component> component);


private:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT>		_components; //일반적인 컴포넌트의 경우, 고정적인 슬롯을 사용하므로 array 사용
	vector<shared_ptr<MonoBehaviour>>						_scripts;	//유저가 커스텀으로 관리할 것들은 따로 관리 ㅇㅋ? 갯수몰라서
};	

