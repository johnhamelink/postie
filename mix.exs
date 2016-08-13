defmodule Mix.Tasks.Compile.Cmake do
  @shortdoc "Compiles helper in src"

  def run(_) do
    {result, _error_code} = System.cmd("cmake", ["."], stderr_to_stdout: true)
    Mix.shell.info result
    {result, _error_code} = System.cmd("make", ["all"], stderr_to_stdout: true)
    Mix.shell.info result
    :ok
  end
end

defmodule Postie.Mixfile do
  use Mix.Project

  def project do
    [app: :postie,
     version: "0.0.1",
     elixir: "~> 1.2-dev",
     build_embedded: Mix.env == :prod,
     start_permanent: Mix.env == :prod,
     compilers: [:cmake] ++ Mix.compilers,
     deps: deps]
  end

  # Configuration for the OTP application
  #
  # Type "mix help compile.app" for more information
  def application do
    [applications: [:logger]]
  end

  # Dependencies can be Hex packages:
  #
  #   {:mydep, "~> 0.3.0"}
  #
  # Or git/path repositories:
  #
  #   {:mydep, git: "https://github.com/elixir-lang/mydep.git", tag: "0.1.0"}
  #
  # Type "mix help deps" for more examples and options
  defp deps do
    []
  end
end

