#include "gtest/gtest.h"
#include "RobotAssembler.h"

namespace ra = cnoid::robot_assembler;
TEST(configtest, loadtest) {
    ra::SettingsPtr _ra_settings = std::make_shared<ra::Settings> ();
    ASSERT_TRUE(_ra_settings->parseYaml("/choreonoid_src/choreonoid/ext/robot_assembler_plugin/config/config_repo_test/irsl_assembler_config.yaml"));
}

