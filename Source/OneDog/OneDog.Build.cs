// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class OneDog : ModuleRules
{
	public OneDog(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Sockets", "Networking", "UMG"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_ARENA=0");
		PublicDefinitions.Add("GOOGLE_PROTOBUF_INTERNAL_DONATE_STEAL_INLINE=0");
		PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI");
		PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS");
		
		PublicIncludePaths.Add("D:\\Study\\Project\\UE5\\OneDog\\ThirdParty\\Protobuf\\include");
		PrivateIncludePaths.Add("D:\\Study\\Project\\UE5\\OneDog\\ThirdParty\\Protobuf\\include");
		PublicSystemIncludePaths.Add("D:\\Study\\Project\\UE5\\OneDog\\ThirdParty\\Protobuf\\include");
		PublicAdditionalLibraries.Add("D:\\Study\\Project\\UE5\\OneDog\\ThirdParty\\Protobuf\\lib\\libprotobuf.lib");
		// PublicAdditionalLibraries.Add("D:\\Study\\Project\\UE5\\OneDog\\ThirdParty\\Protobuf\\lib\\libprotobuf-lite.lib");
		// PublicAdditionalLibraries.Add("D:\\Study\\Project\\UE5\\OneDog\\ThirdParty\\Protobuf\\lib\\libprotoc.lib");


		// PublicDefinitions.Add("PROTOBUF_ENABLE_DEBUG_LOGGING_MAY_LEAK_PII=1");
		// PublicDefinitions.Add("PROTOBUF_BUILTIN_ATOMIC=1");
		// // PublicDefinitions.Add("ABSL_INTERNAL_HAS_RTTI=1");
		//
		// // 添加 Protobuf 的路径
		// string ProtobufPath = "D:\\Study\\Project\\UE5\\OneDog\\ThirdParty\\Protobuf";
		//
		// // 添加头文件路径
		// PublicIncludePaths.Add("D:\\Study\\Project\\vcpkg\\installed\\x64-windows\\include");
		// PublicIncludePaths.Add("D:\\Study\\Project\\UE5\\OneDog\\ThirdParty\\Protobuf\\include");
		// // PublicIncludePaths.Add("C:\\Users\\42276\\Downloads\\protobuf-25.1\\src");
		//
		// // PublicSystemIncludePaths.Add(Path.Combine(ProtobufPath, "include"));
		// // PublicSystemIncludePaths.Add(Path.Combine(ProtobufPath, "lib"));
		// // 添加库路径
		// // PublicAdditionalLibraries.Add("D:\\Study\\Project\\UE5\\OneDog\\ThirdParty\\Protobuf\\lib\\libprotobuf.lib");
		// PublicAdditionalLibraries.Add("D:\\Study\\Project\\vcpkg\\installed\\x64-windows\\lib\\libprotobuf.lib");
		// PublicAdditionalLibraries.Add("D:\\Study\\Project\\vcpkg\\installed\\x64-windows\\lib\\libprotobuf.lib");
		// PublicAdditionalLibraries.Add("D:\\Study\\Project\\vcpkg\\installed\\x64-windows\\lib\\libprotobuf.lib");
		// PublicAdditionalLibraries.Add("D:\\Study\\Project\\vcpkg\\installed\\x64-windows\\lib\\abseil_dll.lib");
		
		// PublicAdditionalLibraries.Add("D:\\Study\\Project\\UE5\\OneDog\\ThirdParty\\Protobuf\\lib\\libprotoc.lib");

		// 添加需要设置的宏
		// PublicDefinitions.Add("GOOGLE_PROTOBUF_INTERNAL_DONATE_STEAL_INLINE=0");
		//
		// PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI");
		// PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS");

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
