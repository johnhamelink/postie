defmodule Postie do
  @on_load :init

  def init do
    path = Application.app_dir(:postie, "priv/postie") |> String.to_char_list
    :ok = :erlang.load_nif(path, 0)
  end

  def expand_address(_address), do: exit(:nif_not_loaded)
  def parse_address(_address), do: exit(:nif_not_loaded)
end
