#pragma once

#include "GameObject.h"

/* ObjectHandle class to 'handle' the lifetime of Game object instances */

template <typename T>
class ObjectHandler {
	T* gameObject = nullptr;
public:
	ObjectHandler() {}
	~ObjectHandler() { delete gameObject; }

	T* operator->() const { return gameObject; };
	T& operator*() const { return *gameObject; };

	void setObjectHandler(T* objectToBeHandled) {
		gameObject = objectToBeHandled;
	}
};