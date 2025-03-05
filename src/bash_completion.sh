#!/bin/bash

_srm_completions() {
  local cur prev opts
  COMPREPLY=()
  cur="${COMP_WORDS[COMP_CWORD]}"
  prev="${COMP_WORDS[COMP_CWORD-1]}"

  # Define options
  opts="--list --restore --restore-all --purge"

  # If restoring, suggest files from /recycle/
  if [[ "$prev" == "--restore" ]]; then
    COMPREPLY=( $(compgen -W "$(ls /recycle/ 2>/dev/null | sed 's/^[^_]*_//')" -- "$cur") )
    return 0
  fi

  # Default completion for options
  COMPREPLY=( $(compgen -W "$opts" -- "$cur") )
  return 0
}

complete -F _srm_completions srm
