#include "pch.h"
#include "Properties.h"



Properties::Properties(std::string dir, std::string description, Point size) : size(size), description(description)
{
	if (dir != "")
	{
		image.loadFromFile("images/items/" + dir);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
}



Properties::Properties(std::string dir, int frames, std::string interaction, Point size) : size(size), update(update), interaction(interaction)
{
	if (frames)
	{
		status.resize(frames);
		for (int i = 0; i < frames; ++i)
		{
			image.loadFromFile("images/objects/" + dir + std::to_string(i + 1) + ".PNG");
			texture.loadFromImage(image);
			status[i].setTexture(texture);
		}
	}
	if (dir != "")
	{
		image.loadFromFile("images/objects/" + dir.substr(0, dir.find('/')) + ".PNG");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
}



void PropertyList::ItemFiller(std::wstring directory)
{
	directory += L"items/";
	items.insert(std::make_pair(L"EMPTY", new Properties("", "", Point(1, 1))));
	items.insert(std::make_pair(L"SEE_TOP", new Properties("", "", Point(1, 1))));
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

			items.insert(std::make_pair(name.substr(0, name.find('.')), new Properties(dir, description, size)));

			fin.close();

		}
		while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}

}



void PropertyList::ObjectFiller(std::wstring directory)
{
	directory += L"objects/";
	items.insert(std::make_pair(L"EMPTY", new Properties("", "", Point(1, 1))));
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
			std::string buff, dir, interaction;
			int frames;
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
				else if (buff == "frames:")
				{
					std::getline(fin, buff);
					frames = stoi(buff.substr(1, buff.length() - 1));
				}
				else if (buff == "interaction:")
				{
					std::getline(fin, buff);
					interaction = buff.substr(1, buff.length() - 1);
				}
				std::getline(fin, buff);
			}

			items.insert(std::make_pair(name.substr(0, name.find('.')), new Properties(dir, frames, interaction, size)));

			/*std::cout <<
				"dir: " << dir << '\n' <<
				"size:" << "\n\t" << "x: " << size.x << "\n\t" << "y: " << size.y << '\n' <<
				"description: \n" << description << '\n';*/

			fin.close();

		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
}



PropertyList::PropertyList(std::wstring dir)
{
	this->ItemFiller(dir);
	this->ObjectFiller(dir);
}