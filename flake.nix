{
  inputs.nixpkgs.url = "nixpkgs/nixos-20.09";

  outputs = { self, nixpkgs }:
  let
    system = "x86_64-linux";
    pkgs   = nixpkgs.legacyPackages.${system};

  in {
    # Shell needed for the SDK to configure itself and build.
    devShell.x86_64-linux = pkgs.mkShell {
      nativeBuildInputs = with pkgs; [
        clang-tools
        pkg-config
        python3Minimal
        valgrind
      ];
      buildInputs = with pkgs; [ curl ncurses ];
    };
  };
}
