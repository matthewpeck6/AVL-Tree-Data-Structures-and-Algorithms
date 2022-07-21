// GatorAVLProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
using namespace std;
class Node
{
//public:
  //  class Node {
    public:
        //Node* head = nullptr;
        string name; // The name serves as the name inputted.
        //T key; //supposed to represent the value (represented as x)
        int value;
        int height = 1;
        Node* left = nullptr;
        Node* right = nullptr;
        
    //};
    //Node* node = nullptr;
    
};

int levelCount(Node* node)
{
    if (node == nullptr) {
        cout << "0" << endl;
        return 0;
    }
    cout << node->height << endl;
    return node->height;
}

Node* rotateLeft(Node* node)
{

    //your code here
    //Node *newNode = node->right;
    Node* newNode = node->right->left;
    Node* tempNode = newNode->left;

    // Perform rotation
    newNode->left = node;
    node->right = tempNode;

    //Need to increase height on left side
    node->height = 1 + max((node->left->height), (node->right->height));
    newNode->height = 1 + max((node->left->height), (node->right->height));
    //std::cout << newNode;
    return newNode;



}

Node* rotateRight(Node* node)
{

    // Perform rotation
    //Need to increase height on left side
    //std::cout << newNode->name;
    //Node* newNode = node->left->right;

    Node* newNode = node->left;
    Node* tempNode = newNode->right; //left of 4 and right of 2 were separated here
    newNode->right = node;
    node->left = tempNode;
    node->height = 1 + max((node->left->height), (node->right->height));
    newNode->height = 1 + max((node->left->height), (node->right->height));
    //newNode->height = 1 + max(height(newNode->left), height(newNode->right)); (also for node)
    return newNode;

    
    

    //your code here
    
}

Node* rotateLeftRight(Node* node)
{
    //your code here
    rotateLeft(node);
    rotateRight(node);
    return node;
}

Node* rotateRightLeft(Node* node)
{
    //your code here
    rotateRight(node);
    rotateLeft(node);
    return node;
}
void PreOrder(Node* node)
{
    if (node != nullptr)
    {
        cout << node->value << " ";
        PreOrder(node->left);
        PreOrder(node->right);
    }
}

void InOrder(Node* node)
{
    if (node != nullptr) {
        InOrder(node->left);
        cout << node->value << " ";
        InOrder(node->right);
    }

}

void PostOrder(Node* node)
{
    if (node != nullptr)
    {
        PostOrder(node->left);
        PostOrder(node->right);
        cout << node->value << " ";
    }

}

//might need a check Insert to see if the parameters are met, if so return true, else return false
Node* insert(Node* node, string NameVal, int IDVal) {
    if (node == nullptr) {
        //For both noNode and inserting Nodes
        Node* temp = new Node();
        temp->name = NameVal;
        temp->value = IDVal;
        temp->height = 1;
        temp->left = nullptr;
        temp->right = nullptr;
        cout << "successful, no previous node" << endl;
        return temp;
    }
    if (IDVal < node->value) {
        node->left = insert(node->left, NameVal, IDVal);
    } else if (IDVal > node->value) {
        node->right = insert(node->right, NameVal, IDVal);
    }

    //Now to check for balance
    node->height = 1 + max((node->left->height), (node->right->height));
    int balance = (node->left->height) - (node->right->height);
    if (balance > 1) {
        if (node->value < node->left->value) {
            return rotateRight(node);
        } else {
            return rotateLeftRight(node);
        }
    }
    else if (balance < -1) {
        if (node->value > node->right->value) {
            return rotateLeft(node);
        }
        else {
            return rotateRightLeft(node);
        }
    } else {
        return node;
    }

    return node;
}

Node* findMinValRightSide(Node* node) {
    if (node != nullptr)
    {
        findMinValRightSide(node->left);
    }
    return node;
}

Node* findMaxValLeftSide(Node* node) {
    if (node != nullptr)
    {
        findMaxValLeftSide(node->right);
    }
    return node;
}

Node* remove(Node* node, string NameVal, int IDVal) {
    if (node == nullptr) {
        //No node in the list
        cout << "unsuccessful nullptr" << endl;
        return NULL;
    }
    if (IDVal < node->value) {

        node->left = remove(node->left, NameVal, IDVal);
    } else if (IDVal > node->value) {
        node->right = remove(node->right, NameVal, IDVal);
    } else if (IDVal == node->value) {
        cout << "found value " << endl;
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
            return node;
        } else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
            return node;
        } else if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
            return node;
        } else {
            Node* temp = findMinValRightSide(node->right);
            node->value = temp->value;
            node->right = remove(node->right, NameVal, temp->value);

        }

    } else {
        cout << "unsuccessful, node not there" << endl;
        return nullptr;
    }

    return node;
    //node->height = 1 + max((node->left->height), (node->right->height));

    

}

Node* removeNthPlace(Node* node, int Nth, int current) {
    int itierator = current;
    if (node != nullptr) {
        if (Nth != current) {
            //if (node != nullptr) {
            itierator++;
            removeNthPlace(node->left, Nth, itierator);
            //cout << node->value << " ";
            removeNthPlace(node->right, Nth, itierator);
            //}
        } else {
            cout << "found value " << endl;
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
                return node;
            }
            else if (node->right == nullptr) {
                Node* temp = node;
                node = node->left;
                delete temp;
                return node;
            }
            else if (node->left == nullptr) {
                Node* temp = node;
                node = node->right;
                delete temp;
                return node;
            }
            else {
                //Have to do Case 4 for this
                //Node* temp = findMinValRightSide(node->right);
                //node->value = temp->value;
                //node->right = remove(node->right, NameVal, temp->value);

            }
            return node;
        }
    } else {
        cout << "unsuccessful nullptr node" << endl;
        return NULL;
    }
    return node;
}

Node* searchID(Node* node, int searchVal) {
    if (node == nullptr) {
        cout << "unsuccessful nullptr node" << endl;
        return NULL;
    }
    if (node->value == searchVal) {
        cout << "successful" << endl;
        cout << node->name << endl;
            return node;
    } else if (node->value > searchVal) {
        searchID(node->left, searchVal); //w & /wo return statement?
    } else if (node->value < searchVal) {
        searchID(node->right, searchVal); //w & /wo return statement?
    } else {
        return NULL;
    }
    return NULL;
}

Node* searchName(Node* node, string searchString) {
    if (node == nullptr) {
        cout << "unsuccessful, nullptr node" << endl;
        return NULL;
    }
    if (node->name.compare(searchString) == 0) {
        cout << "successful" << endl;
        cout << node->value << endl;
        return node;
    } else {
        //how to know if I should go left or right
        //Still use id to check but cout and return string?
        searchName(node->left, searchString);
        searchName(node->right, searchString);
    }
    return NULL;
}

bool checkValidity(string command, string name, unsigned int GatorID, string tempGatorID, Node* newNode) {
    bool parity = false;
    string nothing = "";
    /*
    Node* newNode = new Node();
    newNode->value = GatorID;
    newNode->name = name;
    */
    

    //Check other 8 commands
    if (command.compare("printPreorder") == 0) {
        cout << "Command is printPreorder" << endl;
        //PreOrder(newNode);
        parity = true;
        return parity;
    } else if (command.compare("printInorder") == 0) {
        cout << "Command is printInorder" << endl;
        //InOrder(newNode);
        parity = true;
        return parity;
    } else if (command.compare("printPostorder") == 0) {
        cout << "Command is printPostorder" << endl;
        //PostOrder(newNode);
        parity = true;
        return parity;
    } else if (command.compare("printLevelCount") == 0) {
        cout << "Command is printLevelCount" << endl;
        //levelCount(newNode);
        parity = true;
        return parity;
    }
    
    if (name.compare(nothing) != 0 && tempGatorID.length() == 8) {
        if (command.compare("insert") == 0) {
            //cout << "Command is insert" << endl;
            //newNode = insert(newNode, name, GatorID);
            parity = true;
        }
    }
    if (tempGatorID.length() == 8) {
        if (command.compare("search") == 0) {
            cout << "Command is search ID" << endl;
            //newNode = searchID(newNode, GatorID);
            parity = true;
        } else if (command.compare("remove") == 0) {
            cout << "Command is remove" << endl;
            //newNode = remove(newNode, name, GatorID);
            parity = true;
        }
    }
    
    if (name.compare(nothing) != 0 && GatorID == 0){
        if (command.compare("search") == 0) {
            cout << "Command is search name" << endl;
            //newNode = searchName(newNode, name);
            parity = true;
        }
    }
    
    return parity;
}

int main()
{
    //Node* node = nullptr;
    std::cout << "How many inputs do you want to try and put in: ";
    string inputs = "";
    getline(cin, inputs);
    int number = 0;
    number = stoi(inputs);
    Node* newNode = nullptr;
    
    //for (int i = 0; i < number; i++) { cout << i << endl; }
    int itCheck = 0;
    string command = "";
    string name = "";
    string inCaseSpace = "";
    int GatorID = 0;
    string tempGatorID = "";
    unsigned int pos = 0;

    for (int i = 0; i < number; i++) {
        std::cout << "What command do you want to do: ";
        getline(cin, inputs);
        string delimiter = "\"";
        string delimiterOne = " ";

        pos = inputs.find(delimiterOne);
        command = inputs.substr(0, pos);
        //cout << "Command: " << command << endl; print debug
        inputs.erase(0, pos + delimiterOne.length());

        pos = inputs.find(delimiter);
        inCaseSpace = inputs.substr(0, pos);
        //cout << "Temporary Check: " << inCaseSpace << endl; print debug
        inputs.erase(0, pos + delimiter.length());

        pos = inputs.find(delimiter);
        name = inputs.substr(0, pos);
        //cout << "Name: " << name << endl; print debug
        inputs.erase(0, pos + delimiter.length());

        pos = inputs.find(delimiter);
        tempGatorID = inputs.substr(0, pos);
        tempGatorID.erase(remove_if(tempGatorID.begin(), tempGatorID.end(), isspace), tempGatorID.end());
        //cout << "New Temp Gator ID: " << tempGatorID << endl; print debug
        inputs.erase(0, pos + delimiter.length());

        try {
            GatorID = stoi(tempGatorID);
            //cout << "Gator ID: " << GatorID << endl;
        }
        catch (std::invalid_argument& e) {
            //cout << "no conversion could be performed" << endl;
            name = tempGatorID;
            //cout << "New Name: " << name << endl;
        }

        //cout << "Gator ID: " << GatorID << endl; print debug
        if (command.compare("removeInorder") == 0) {
            cout << "Command is removeInorder" << endl;
            int current = 0;
            newNode = removeNthPlace(newNode, GatorID, current);
        }
        //Have to consider cases of Remove and Prints

        /*
        Node* temp = new Node();
        temp->value = GatorID;
        temp->name = name;
        temp->height = 1;
        temp->left = nullptr;
        temp->right = nullptr;
        */
        
        //checkValidity(command, name, GatorID, tempGatorID, temp);
        checkValidity(command, name, GatorID, tempGatorID, newNode);

        
        if (command.compare("printPreorder") == 0) {
            cout << "Command is printPreorder Main" << endl;
            PreOrder(newNode);
        } else if (command.compare("printInorder") == 0) {
            cout << "Command is printInorder Main" << endl;
            InOrder(newNode);
        } else if (command.compare("printPostorder") == 0) {
            cout << "Command is printPostorder Main" << endl;
            PostOrder(newNode);
        } else if (command.compare("printLevelCount") == 0) {
            cout << "Command is printLevelCount Main" << endl;
            levelCount(newNode);

        } else if (command.compare("insert") == 0) {
            cout << "Command is insert Main" << endl;
            if (itCheck == 1) {
                cout << endl;
                cout << "Before crash" << endl;
                cout << "Root Node values" << endl;
                cout << "NewNode Value: " << newNode->value << endl;
                cout << "NewNode Name: " << newNode->name << endl;
                cout << "NewNode Height: " << newNode->height << endl;
                cout << "NewNode Left: " << newNode->left << endl;
                cout << "NewNode Right: " << newNode->right << endl;
            }
            
            newNode = insert(newNode, name, GatorID);

            itCheck++;

        } else if (command.compare("remove") == 0) {
            cout << "Command is remove Main" << endl;
            newNode = remove(newNode, name, GatorID);
        } else if (GatorID == 0) {
                if (command.compare("search") == 0) {
                    cout << "Command is search name Main" << endl;
                    newNode = searchName(newNode, name);
                    
                }
        } else if (command.compare("search") == 0) {
            cout << "Command is search ID Main" << endl;
            newNode = searchID(newNode, GatorID);
        }
        


        command = "";
        name = "";
        inCaseSpace = "";
        GatorID = 0;
        tempGatorID = "";
        inputs = "";
        pos = 0;
        cout << endl;
    }
    
}




//cout << "Temp Gator ID: " << tempGatorID << endl; //String version of Gator ID
//remove(tempGatorID.begin(), tempGatorID.end(), ' ');

/*
cout << "NewNode Value: " << newNode->value << endl;
cout << "NewNode Name: " << newNode->name << endl;
cout << "NewNode Height: " << newNode->height << endl;
cout << "NewNode Left Value: " << newNode->left << endl;
cout << "NewNode Right Value: " << newNode->right << endl;
*/



/*
else if (command.compare("search") == 0) {
    cout << "Command is search name" << endl;
    newNode = searchName(newNode, name);
    parity = true;
}
*/

/*
if (name.compare(nothing) != 0 && tempGatorID.length() == 8) {
    if (command.compare("insert") == 0) {
        cout << "Command is insert" << endl;
        parity = true;
    } else if (command.compare("remove") == 0) {
        cout << "Command is remove" << endl;
        parity = true;
    }  else if (command.compare("search") == 0) {
        cout << "Command is search" << endl;
        parity = true;
    } else if (command.compare("printLevelCount") == 0) {
        cout << "Command is printLevelCount" << endl;
        parity = true;
    }
}
*/

/*


//left child is null or both are null
if (node->left == nullptr) {
    return node->right;
//right is null
} else if (node->right == nullptr) {
    return node->left;
} else {
//neither are null, both left and right child have values
    if (node->left->height > node->right->height) {
        //Remove from left side of subtree
        int newVal = findMax(node->left);
        node->value = newVal;

        node->left = remove(node->left, NameVal, newVal);
    } else {
        //Remove from right side of subtree
        int newVal = findMin(node->right);
        node->value = newVal;

        node->right = remove(node->right, NameVal, newVal);
    }

}
//Find successor nodes
//check node->left and node-> right
// if both nullptr, just remove
// if only 1 is nullptr, make successor the child node not nullptr
//Now to check for balance


*/

    //cout << s << endl;
    /*
        while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        std::cout << token << std::endl;
        s.erase(0, pos + delimiter.length());
    }    
    */

    //std::cout << s << std::endl;
    /*
    string inputs = "";
    string delimiters = "";
    int tempDelimiter = 0;
    std::string s = "scott>=tiger";
    s = "scott>=tiger";
    cout << s << endl;
    std::string delimiter = ">=";
    std::string token = s.substr(0, s.find(delimiter)); // token is "scott"

    getline(cin, inputs);
    delimiters = "\"";
    tempDelimiter = inputs.find(delimiters);
    //First string with command
    command = inputs.substr(0, tempDelimiter);
    //Second string with the name
    name = inputs.substr(tempDelimiter, inputs.find(delimiter));

    while (getline(inFile, lineFromFile)) {
        istringstream stream(lineFromFile);

        

        getline(stream, command, '"');
        getline(stream, name, '"');
        getline(stream, tempGatorID);
        GatorID = stoi(tempGatorID);



    }
    */
    




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
