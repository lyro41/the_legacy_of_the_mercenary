#include "pch.h"
#include "Properties.h"



Properties::Properties(std::string dir, std::string description, Point size) : size(size), description(description)
{
	if (dir != "")
	{
		image.loadFromFile("images/" + dir);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
}



void PropertyList::Filler(std::wstring directory)
{
	properties.insert(std::make_pair(L"EMPTY", new Properties("", "", Point(1, 1))));
	std::ifstream fin;
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	std::wstring search = directory + L"*.txt";
	hf = FindFirstFile(search.c_str(), &FindFileData);
	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			std::wstring name = FindFileData.cFileName;
			std::string buff, dir, description = "";
			Point size;
			fin.open(directory + name, std::ios_base::in);

			while (!fin.eof())
			{
				fin >> buff;
				if (buff == "dir:")
				{
					std::getline(fin, buff);
					dir = buff.substr(1, buff.length() - 1);
				}
				else if (buff == "size:")
				{
					std::getline(fin, buff);
					auto i = buff.find('x');
					size.x = std::stoi(buff.substr(0, i));
					size.y = std::stoi(buff.substr(i + 1, buff.length() - i - 1));
				}
				else if (buff == "description:")
				{
					std::getline(fin, buff);
					std::getline(fin, buff);
					while (buff != "}")
					{
						description += buff + '\n';
						std::getline(fin, buff);
					}
				}
				std::getline(fin, buff);
			}

			properties.insert(std::make_pair(name, new Properties(dir, description, size)));

			/*std::cout <<
				"dir: " << dir << '\n' <<
				"size:" << "\n\t" << "x: " << size.x << "\n\t" << "y: " << size.y << '\n' <<
				"description: \n" << description << '\n';*/

			fin.close();

		}
		while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}

}



PropertyList::PropertyList(std::wstring dir)
{
	this->Filler(dir);
}

