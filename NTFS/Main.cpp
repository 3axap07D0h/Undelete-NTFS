#include "PartitionTableParser.h"
#include "DrivesInfo.h"
#include "MFTParser.h"

#include <iostream>

int main(int argc, char** argv)
{
	try
	{
		PartitionTableParser parser;
		parser.parse();

		try
		{
			ntfs::DrivesInfo di(parser.getLogicalDrives());
			di.getDrivesInfo();

			auto pDrivesMft = di.getDrivesMFT();

			for (auto it = pDrivesMft->cbegin(); it != pDrivesMft->cend(); ++it)
			{
				ntfs::MFTParser mftParser(*it);
				mftParser.readFirstRecord();
			}
		}
		catch (std::logic_error error)
		{
			std::cout << error.what();
		}
	}
	catch (std::runtime_error error)
	{
		std::cout << error.what() << std::endl;
	}

	system("pause");
	return 0;
}