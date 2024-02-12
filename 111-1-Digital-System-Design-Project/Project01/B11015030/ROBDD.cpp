#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <algorithm>
using namespace std;

struct node
{
   string label = "";
   int condition;
   int then_edge;
   int else_edge;
};

void tableInit(vector<node> &arr, vector<string> &labelName, int &inputNum);
void recursion(int index, int step, vector<node> &arr, string &product, int &inputNum);
vector<bool> to_Binary(int x, int inputNum);
void simplify(vector<node> &arr, int &inputNum);
int findParent(int index, vector<node> &arr);
bool isSimple(vector<node> &arr, int &inputNum);

int main(int argc, char *argv[])
{
   ifstream input_file;
   ofstream output_file;
   input_file.open(argv[1]);
   output_file.open(argv[2]);

   vector<node> arr;
   int inputNum = 0;          // .i
   int outputNum = 0;         // .o
   vector<string> labelName;  // .ilb
   vector<string> outputName; // .ob
   int productNum = 0;        // .p => product term number

   vector<string> equ;
   while (input_file.good())
   {
      string type;
      string name;
      int num;
      int lowIndex = 0;
      int highIndex = pow(2.0, inputNum);
      input_file >> type;
      if (type == ".i")
      {
         input_file >> num;
         inputNum = num;
         arr.resize(1 + pow(2.0, inputNum));
      }
      else if (type == ".o")
      {
         input_file >> num;
         outputNum = num;
      }
      else if (type == ".ilb")
      {
         for (int i = 0; i < inputNum; i++)
         {
            input_file >> name;
            labelName.push_back(name);
         }
      }
      else if (type == ".ob")
      {
         for (int i = 0; i < outputNum; i++)
         {
            input_file >> name;
            outputName.push_back(name);
         }
      }
      else if (type == ".p")
      {
         input_file >> num;
         productNum = num;
      }
      else if (type == ".e")
      {
         continue;
      }
      else
      {
         tableInit(arr, labelName, inputNum);
         // init end edge is 8 => boolean 0
         bool f;
         input_file >> f;
         if (f == 1)
         {
            equ.push_back(type);
         }
      }
   }
   for (auto val : equ)
   {
      recursion(1, 0, arr, val, inputNum);
   }

   for (auto val1 : arr)
   {
      cout << val1.label << " " << val1.then_edge << " " << val1.else_edge << " " << val1.condition << endl;
   }
   cout << "-------------------------------------------\n";
   while (isSimple(arr, inputNum) == 0)
   {
      simplify(arr, inputNum);
   }

   for (auto val1 : arr)
   {
      cout << val1.label << " " << val1.then_edge << " " << val1.else_edge << " " << val1.condition << endl;
   }

   // Write .dot file to output_file
   /////////////////////////////////////////////////////////////////
   output_file << "digraph ROBDD {\n";
   for (auto label : labelName)
   {
      string sameRank = "";
      for (int i = 0; i < arr.size() - 1; i++)
      {
         if (arr[i].label == label && arr[i].condition == 0)
         {
            sameRank += " " + to_string(i);
         }
      }
      output_file << "  {rank=same" << sameRank << "}\n";
   }
   output_file << "\n  0 [label=\"0\", shape=box];\n";
   for (auto label : labelName)
   {
      vector<int> labelIndex;
      for (int i = 0; i < arr.size() - 1; i++)
      {
         if (arr[i].label == label && arr[i].condition == 0)
         {
            labelIndex.push_back(i);
         }
      }
      for (auto index : labelIndex)
      {
         string setLabel;
         setLabel += "  " + to_string(index) + " [label=\"" + label + "\"]\n";
         output_file << setLabel;
      }
   }
   output_file << "  " << to_string(arr.size() - 1) << " [label=\"1\", shape=box];\n\n";

   for (int i = 1; i < arr.size() - 1; i++)
   {
      if (arr[i].condition == 0)
      {
         string draw;
         // else_edge
         draw = "  " + to_string(i) + " -> " + to_string(arr[i].else_edge) + " [label=\"0\", style=dotted]\n";
         output_file << draw;
         // then_edge
         draw = "  " + to_string(i) + " -> " + to_string(arr[i].then_edge) + " [label=\"1\", style=solid]\n";
         output_file << draw;
      }
   }
   output_file << "}\n";
   /////////////////////////////////////////////////////////////////
   return 0;
}

void recursion(int index, int step, vector<node> &arr, string &product, int &inputNum)
{
   bool endFlag = 0;
   if (index == 0 || index == pow(2.0, inputNum))
   {
      return;
   }
   if (step == inputNum - 1)
      endFlag = 1;
   if (product[step] == '0')
   {
      if (endFlag)
         arr[index].else_edge = pow(2.0, inputNum);
      recursion(arr[index].else_edge, step + 1, arr, product, inputNum);
   }
   else if (product[step] == '1')
   {
      if (endFlag)
         arr[index].then_edge = pow(2.0, inputNum);
      recursion(arr[index].then_edge, step + 1, arr, product, inputNum);
   }
   else if (product[step] == '-')
   {
      if (endFlag)
         arr[index].else_edge = pow(2.0, inputNum);
      if (endFlag)
         arr[index].then_edge = pow(2.0, inputNum);
      recursion(arr[index].else_edge, step + 1, arr, product, inputNum);
      recursion(arr[index].then_edge, step + 1, arr, product, inputNum);
   }
}

void tableInit(vector<node> &arr, vector<string> &labelName, int &inputNum)
{
   arr[0].label = "0";
   arr[pow(2.0, inputNum)].label = "1";
   for (int level = 1, var = 1; level <= inputNum; level++, var *= 2)
   {
      for (int index = var; index < var * 2; index++)
      {
         arr[index].label = labelName[level - 1];
         if (index * 2 < pow(2.0, inputNum))
         {
            arr[index].then_edge = index * 2;
            arr[index].else_edge = index * 2 + 1;
         }
         else
         {
            arr[index].then_edge = 0;
            arr[index].else_edge = 0;
         }
      }
   }
}

void simplify(vector<node> &arr, int &inputNum)
{
   // delete the node have same edge
   int deleteIndex;
   int edgeIndex;
   int ParentIndex;
   for (int i = arr.size() - 2; i >= 1; i--)
   {
      if (arr[i].else_edge == arr[i].then_edge)
      {
         // cout << "same edge index => " << i << endl;
         deleteIndex = i;
         edgeIndex = arr[i].else_edge;
         ParentIndex = findParent(deleteIndex, arr);
         while (ParentIndex != -1)
         {
            ParentIndex = findParent(deleteIndex, arr);
            if (arr[ParentIndex].else_edge == deleteIndex)
               arr[ParentIndex].else_edge = edgeIndex;
            if (arr[ParentIndex].then_edge == deleteIndex)
               arr[ParentIndex].then_edge = edgeIndex;
         }
         arr[deleteIndex].condition = -1; // condition = -1 => redundant
      }
   }
   for (int i = arr.size() - 2; i >= 1; i--)
   {
      for (int j = i - 1; j >= 0; j--)
      {
         if (arr[i].label != arr[j].label)
            continue;
         if (arr[i].else_edge == arr[j].else_edge && arr[i].then_edge == arr[j].then_edge)
         {
            // 保留j，移除i
            deleteIndex = i;
            ParentIndex = findParent(deleteIndex, arr);
            while (ParentIndex != -1)
            {
               ParentIndex = findParent(deleteIndex, arr);
               if (arr[ParentIndex].else_edge == deleteIndex)
               {
                  arr[ParentIndex].else_edge = j;
               }
               if (arr[ParentIndex].then_edge == deleteIndex)
               {
                  arr[ParentIndex].then_edge = j;
               }
            }
            arr[deleteIndex].condition = -1; // condition = -1 => redundant
         }
      }
   }
}

bool isSimple(vector<node> &arr, int &inputNum)
{
   for (int i = arr.size() - 2; i >= 1; i--)
   {
      if (arr[i].condition == -1)
         continue;
      if (arr[i].else_edge == arr[i].then_edge)
         return 0;
      for (int j = i - 1; j >= 0; j--)
      {
         if (arr[i].label != arr[j].label)
            continue;
         if (arr[i].else_edge == arr[j].else_edge && arr[i].then_edge == arr[j].then_edge)
            return 0;
      }
   }
   return 1;
}

int findParent(int index, vector<node> &arr) // -1 => no found
{
   for (int i = 0; i < arr.size(); i++)
   {
      if (arr[i].else_edge == index)
         return i;
      if (arr[i].then_edge == index)
         return i;
   }
   return -1;
}
