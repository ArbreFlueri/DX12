#pragma once

enum class COMPONENT_TYPE : uint8
{
	TRANSFORM,
	MESH_RENDERER,
	//...TODO...
	MONO_BEHAVIOUR, //반드시 마지막에 와야해
	END,
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<uint8>(COMPONENT_TYPE::END) - 1
}; //monoBehaviour 뺴고 다 자기만의 슬롯이 하나만 있음.


class GameObject;
class Transform;

class Component
{
public :
	Component(COMPONENT_TYPE type);
	virtual ~Component(); 
	// component는 부모클래스이기 때문에 virtual 붙여줘야함

public :
	virtual void Awake()		{ }
	virtual void Start()		{ }
	virtual void Update()		{ }
	virtual void LateUpdate()	{ }

public :
	COMPONENT_TYPE GetType()	{ return _type; }
	bool IsValid()				{ return _gameObject.expired() == false; }

	shared_ptr<GameObject> GetGameObject();
	shared_ptr<Transform> GetTransform();

private:
	friend class GameObject;//gameobject에게만 이곳의 접근권한을 줌
	void SetGameObject(shared_ptr<GameObject> gameObject) { _gameObject = gameObject; }

protected:
	COMPONENT_TYPE			_type;
	weak_ptr<GameObject>	_gameObject;
};

