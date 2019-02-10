


#ifndef FIRESTORM_QUEUEFAMILYINDICES_HPP
#define FIRESTORM_QUEUEFAMILYINDICES_HPP

namespace fs::graphics
{
struct QueueFamilyIndices
{
    int graphicsFamily = -1;
    int presentFamily = -1;

    bool isComplete() const
    {
        return graphicsFamily >= 0 && presentFamily >= 0;
    }
};
}
#endif //FIRESTORM_QUEUEFAMILYINDICES_HPP
