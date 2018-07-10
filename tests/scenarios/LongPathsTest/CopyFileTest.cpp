//-------------------------------------------------------------------------------------------------------
// Copyright (C) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//-------------------------------------------------------------------------------------------------------

#include <test_config.h>

#include "paths.h"

static int DoCopyFileTest()
{
    clean_redirection_path();

    auto copyPath = g_testPath / L"copy.txt";
    trace_messages(L"Copying from: ", info_color, g_testFilePath.native(), new_line);
    trace_messages(L"          to: ", info_color, copyPath.native(), new_line);

    if (!::CopyFileW(g_testFilePath.c_str(), copyPath.c_str(), false))
    {
        return trace_last_error(L"CopyFile failed");
    }
    else if (auto contents = read_entire_file(copyPath.c_str()); contents != g_expectedFileContents)
    {
        trace_message(L"ERROR: Copied file contents do not match expected contents\n", error_color);
        trace_messages(error_color, L"ERROR: Expected contents: ", error_info_color, g_expectedFileContents, new_line);
        trace_messages(error_color, L"ERROR: File contents: ", error_info_color, contents, new_line);
        return ERROR_ASSERTION_FAILURE;
    }

    return ERROR_SUCCESS;
}

int CopyFileTest()
{
    test_begin("CopyFile Test");
    auto result = DoCopyFileTest();
    test_end(result);
    return result;
}
