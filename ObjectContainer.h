#pragma once
#include <memory>
#include <string>
#include <map>

// Forward declare reference-looped class
class Object3D;

typedef std::map<std::string, std::shared_ptr<Object3D>>::iterator ObjectIterator;
typedef std::map<std::string, std::shared_ptr<Object3D>>::const_iterator ConstObjectIterator;

typedef std::pair<std::string, std::shared_ptr<Object3D>> LabelObjectPair;
typedef const std::pair<std::string, std::shared_ptr<Object3D>> ConstLabelObjectPair;

class ObjectContainer
{
public:
	void AddObjectPtr(std::shared_ptr<Object3D> objectPtr);
	const std::shared_ptr<Object3D> At(const std::string& uniqueLabel) const;
	void Remove(const std::string& uniqueLabel);
	void Remove(const std::shared_ptr<Object3D>& objectWithLabel);
	unsigned int Size() const;

	std::shared_ptr<Object3D> operator[](const std::string& uniqueLabel);

	ObjectIterator begin() noexcept;
	ObjectIterator end() noexcept;

	ConstObjectIterator begin() const noexcept;
	ConstObjectIterator end() const noexcept;

private:
	std::map<std::string, std::shared_ptr<Object3D>> objectPtrs;
};
