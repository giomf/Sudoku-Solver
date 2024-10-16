{
  description = "A very basic c++ flake";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    flake-utils.inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let pkgs = nixpkgs.legacyPackages.${system};
      in {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            cmake
            cmake-language-server
            llvmPackages_19.clang-tools
            llvmPackages_19.clang
            gdb
            qt6.full
            qtcreator
          ];
          env = { };
          shellHook = ''
            export CC=clang
            export CXX=clang++
          '';
        };
      });
}
