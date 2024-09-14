#include "includes.h"
#include "raylib.h"

bool TraverseImageNodeForward(ImageNode** currentNode)
{
    assert(*currentNode != NULL);
    if ((*currentNode)->next != NULL) {*currentNode = (*currentNode)->next; return true;}
    else return false;
}

bool TraverseImageNodeBackward(ImageNode** currentNode)
{
    assert(*currentNode != NULL);
    if ((*currentNode)->prev != NULL) {*currentNode = (*currentNode)->prev; return true;}
    else return false;
}

// Create new  ImageNode for a doubly linked list with NULL prev and next
ImageNode* NewImageNode(Image image)
{
    ImageNode* node = malloc(sizeof(ImageNode));
    if (node == NULL) {exit(EXIT_FAILURE);}
    node->image = ImageCopy(image);
    node->next = NULL;
    node->prev = NULL;

    return node;
}

// Pass what should be the tail to this function to remove it
void RemoveTailImageNode(ImageNode* tail)
{
    if(tail == NULL)        {exit(EXIT_FAILURE);} // Don't pass a null node lol
    if(tail->prev != NULL)  {exit(EXIT_FAILURE);} // If this is the case, it's not the tail!
    free(tail);
}

// Traverses from current node to head to remove the end and make the head->prev the new head
void RemoveHeadImageNode(ImageNode* currentNode)
{
    assert(currentNode != NULL); // If this happens, Something went wrong
    assert(currentNode->next != NULL); // Don't call this function if current is also the end!
    while (currentNode->next != NULL) {TraverseImageNodeForward(&currentNode);}
    if (currentNode->prev != NULL) {currentNode->prev->next = NULL;}
    free(currentNode);
}

// Removes all next nodes after current
void ClearNextImageNodes(ImageNode* currentNode)
{
    assert(currentNode != NULL);
    while (currentNode->next != NULL) {RemoveHeadImageNode(currentNode);}
}

// This replaces the currentNode's next node to a new node
void ReplaceNextImageNode(ImageNode** currentNode, Image image)
{
    ImageNode* newNode = NewImageNode(image);
    (*currentNode)->next = newNode;
    newNode->prev = *currentNode;
}