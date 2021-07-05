{
  inputs.nixpkgs.url = "nixpkgs/nixos-20.09";

  outputs = { self, nixpkgs }:
  let
    system = "x86_64-linux";
    pkgs   = nixpkgs.legacyPackages.${system};

  in rec {
    defaultPackage.${system} = pkgs.stdenv.mkDerivation {
      name    = "wrtele";
      version = "git"; # Version doesn't matter because any real build is done
                       # using SDK instead of Nix.
      src     = ./src;

      nativeBuildInputs = with pkgs; [ pkg-config ];
      buildInputs       = with pkgs; [ curl ];

      installPhase = ''
        mkdir -p $out/bin
        cp bin/wrtele $out/bin
      '';
    };

    # Shell needed for the SDK to configure itself and build.
    devShell.${system} = pkgs.mkShell {
      inputsFrom = [ defaultPackage.${system} ];
      nativeBuildInputs = with pkgs; [
        clang-tools
        python3Minimal
        valgrind
      ];
      buildInputs = with pkgs; [ ncurses ];
    };
  };
}
