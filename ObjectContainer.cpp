#include "ObjectContainer.h"
#include "ObjectsBase.h"

void ObjectContainer::AddObjectPtr(std::shared_ptr<Object3D> objectPtr)
{
	objectPtrs[objectPtr->GetLabel()] = objectPtr;
}

const std::shared_ptr<Object3D> ObjectContainer::At(const std::string& uniqueLabel) const
{
	return objectPtrs.at(uniqueLabel);
}

void ObjectContainer::Remove(const std::string& uniqueLabel)
{
	objectPtrs.erase(uniqueLabel);
}

void ObjectContainer::Remove(const std::shared_ptr<Object3D>& objectWithLabel)
{
	objectPtrs.erase(objectWithLabel->GetLabel());
}

std::shared_ptr<Object3D> ObjectContainer::operator[](const std::string& uniqueLabel)
{
	return objectPtrs[uniqueLabel];
}

ObjectIterator ObjectContainer::begin() noexcept
{
	return objectPtrs.begin();
}

ObjectIterator ObjectContainer::ObjectContainer::end() noexcept
{
	return objectPtrs.end();
}

ConstObjectIterator ObjectContainer::begin() const noexcept
{
	return objectPtrs.cbegin();
}

ConstObjectIterator ObjectContainer::ObjectContainer::end() const noexcept
{
	return objectPtrs.cend();
}
