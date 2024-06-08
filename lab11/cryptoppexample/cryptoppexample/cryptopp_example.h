#pragma once
#include <cryptlib.h>

#include <sha.h>
#include <hex.h>
#include <osrng.h>
#include <modes.h>
#include <AES.h>
#include <files.h>
#include <filters.h>

#include <rsa.h>
#include <sha.h>

#include <pssr.h>

namespace cryptoppexample
{
	void symmetric_chipher_dechipher(std::string filename);

	void asymmetric_chipher_dechipher(std::string filename);

	void signer_verifier(std::string filename);

	void hash_file(std::string filename);
}